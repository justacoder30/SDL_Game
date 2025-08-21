#include "Entity.h"
#include <algorithm>
#include <future>
//#include "ThreadPool.h"

//std::vector<Entity*> Collisions;
std::vector<Rect> Collisions;

bool Entity::IsOnGround()
{
    Rect g_rect = GravityRect();
    for (int i = 0; i < Collisions.size(); ++i) {
        if (g_rect.checkCollide(Collisions[i]) ) 
            return true;
    }
    return false;
}

bool Entity::IsBreakLoop()
{
    return breakLoop;
}

void Entity::ChangeLevel()
{
    changeLevel = true;
}

void Entity::UpdateGravity()
{
    isOnGround = IsOnGround();
}

void Entity::UpdateAnimation(const float& dt)
{
    animationManger.Play(animations[current]);
    animationManger.Update(dt);
}

void Entity::DrawRectTransform(Rect r)
{
    Rect newR = r;
    newR.x += Global.camera.transform.x;
    newR.y += Global.camera.transform.y;
    window.DrawRect(newR);
}

void Entity::DrawFillRectTransform(Rect r)
{
    Rect newR = r;
    newR.x += Global.camera.transform.x;
    newR.y += Global.camera.transform.y;
    window.DrawFillRect(newR);
}

void Entity::DrawFillRectStatic(Rect r)
{
    window.DrawFillRect(r);
}

void Entity::DrawRectStatic(Rect r)
{
    window.DrawRect(r);
}


void Entity::beingAttacked(const Entity& entity, const float& dt)
{
    beingAttackTime += dt;
    isHurt = false;

    if (beingAttackTime < AttackStepTime(entity)) return;
    beingAttackTime = 0;
    isHurt = true;
    damageTaken = entity.damage;
    hurtDirection = entity.center_pos.x > center_pos.x ? -1 : 1;
	Global.freezeFrame = 0.1f; // Freeze frame for 0.1 seconds
}

void Entity::beingHurt()
{
    SoundManager::PlaySoundEffect("Hurt");
    velocity.y = -getHitJump;
    currentHp -= damageTaken;
}

//Entity::Entity()
//{}

void Entity::Update(const float& dt)
{
    std::vector<int> toRemove;
	auto& pool = Global.pool;

    for (int i = Entities.size() - 1; i >= 0; --i)
    {
        if (Entities[i]->isChangLevel()) {
            ChangeLevel();
        }

        if (Entities[i]->isRemoved()) {
            toRemove.push_back(i);
        }
    }

    for (int i : toRemove) {
        delete Entities[i];
        Entities.erase(Entities.begin() + i);
    }

	std::vector<Entity*> entities = Entities;

	for (auto& e : entities) {
        pool.enqueue([e, dt]() {
            e->Update(dt);
        });
        //e->Update(dt);
    }

    
}

void Entity::Draw()
{
	Camera& camera = Global.camera;
    for (int i = 0; i < Entities.size(); ++i)
    {
        if (!camera.canSee(Entities[i]->rect) && !Entities[i]->backDrop) continue;
        Entities[i]->Draw();
    }
}

float Entity::AttackStepTime(Entity entity)
{
    return entity.animationManger.animation.FrameSpeed;
}

Entity Entity::add(Entity* entity)
{
    entity->setRemove();
    /*if (std::find(Entities.begin(), Entities.end(), entity) == Entities.end())
    {
        entity->parent = this;
        Entities.push_back(entity);
    }*/

    if (entity->parent != this) {
        entity->parent = this;
        Entities.push_back(entity);
    }

    return *this;
}

void Entity::freeEntities()
{
    for(auto& entity : Entities)
    {
        //if (entity != nullptr) delete entity; 
	}

    for (int i = Entities.size() - 1; i >= 0; --i)
    {
        if (Entities[i] != nullptr) delete Entities[i];
    }
}

void Entity::freeAnimations()
{
    for (auto& anim : animations)
    {
        anim.second.free();
    }
    /*animations.clear();
    animationManger = AnimationManager();
	animationManger.animation = Animation();*/
}

void Entity::add_NoPoitner(Entity& entity)
{
    entity.setRemove();
    Entities.push_back(&entity);
}// Define a mutex for the Collisions vector

void Entity::Collision(std::string direction)
{
    auto& collisions = Collisions;
    rect = Rect(rect.x, rect.y, rect.w, rect.h);
    for (int i = 0; i < collisions.size(); ++i) {
        if (!rect.checkCollide(collisions[i]))
            continue;
        if (direction == "y") {

            if (rect.bottom >= collisions[i].top && old_rect.bottom <= collisions[i].top) 
            //if (velocity.y > 0)
            {
                rect.y += collisions[i].top - rect.bottom;
                rect.bottom = collisions[i].top;
                isOnGround = true;
            }

            if (rect.top <= collisions[i].bottom && old_rect.top >= collisions[i].bottom)
            //if (velocity.y < 0)
            {
                rect.y += collisions[i].bottom - rect.top;
                rect.top = collisions[i].bottom;
                
            }

            velocity.y = 0;
        }
        else {
            if (rect.right >= collisions[i].left && old_rect.right <= collisions[i].left) {
                rect.x += collisions[i].left - rect.right;
                rect.right = collisions[i].left;
            }

            if (rect.left <= collisions[i].right && old_rect.left >= collisions[i].right) {
                rect.x += collisions[i].right - rect.left;
                rect.left = collisions[i].right;
            }

            //velocity.x *= -1;
        }
    }
}

void Entity::SetCollision(float _left, float _top, float _right, float _bottom)
{
    OFFSET.top = _top;
    OFFSET.bottom = _bottom;
    OFFSET.left = _left;
    OFFSET.right = _right;
}

void Entity::DrawAnimateGroup()
{
    window.blit(
        animationManger.animation.texture,
        GetPos() + Global.camera.transform,
        animationManger.getRect(),
        scale,
        animationManger.flip
    );
}

void Entity::removeFromTree()  
{  
    removed = true;  
}

bool Entity::isRemoved()
{
    return removed;
}

void Entity::setRemove()
{
    removed = false;
}

bool Entity::isAttacking()
{
    if (animationManger.animation.CurrentFrame != attackFrame) return false;

    if (current != Attack && 
        current != Attack1 && 
        current != Attack2 && 
        current != Attack3 && 
        current != RunAttack
    ) 
        return false;

    return true;
}

bool Entity::isChangLevel()
{
    return changeLevel;
}

Rect Entity::getAtkBox()
{
    Vector Pos = GetPos();

    if (!animationManger.IsFlip())
        return Rect(Pos.x + atkBox.x, Pos.y + atkBox.y, atkBox.w, atkBox.h);
    return Rect(Pos.x + texture_width * scale - atkBox.x - atkBox.w, Pos.y + atkBox.y, atkBox.w, atkBox.h);
}

Vector Entity::GetPos()
{
    if (!animationManger.IsFlip())
        return Vector(rect.x - OFFSET.left, rect.y - OFFSET.top);
    return Vector(rect.x - OFFSET.right, rect.y - OFFSET.top);
}

Rect Entity::GravityRect()
{
    return Rect(rect.x,
        rect.y + rect.h,
        rect.w,
        1
    );
}

Vector Entity::GetCenter()
{
    float pos_X = rect.x + (rect.w / 2);
    float pos_Y = rect.y + (rect.h / 2);
    return Vector(pos_X, pos_Y);
}

