#include "Entity.h"
#include <algorithm>

//std::vector<Entity*> Collisions;
std::vector<Rect> Collisions;

void Entity::BreakLoop()
{
	breakLoop = true;
}

void Entity::Loop()
{
    breakLoop = false;
}

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

    //std::vector<Entity*> entitiesCopy = Entities; // clone để tránh crash

    //for (Entity* e : entitiesCopy) {
    //    Global.pool.enqueue([e, dt]() {
    //        e->Update(dt); // logic từng entity
    //        });
    //}

    //Global.pool.wait();

    for (int i = Entities.size() - 1; i >= 0; --i)
    {
        Entities[i]->Update(dt);
        if (Entities[i]->IsBreakLoop()) return;

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
    
    //Global.pool.wait();
}

void Entity::Draw()
{
    for (int i = 0; i < Entities.size(); ++i)
    {
        if (!Global.camera.canSee(Entities[i]->rect) && !Entities[i]->backDrop) continue;
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
    if (std::find(Entities.begin(), Entities.end(), entity) == Entities.end())
    {
        Entities.push_back(entity);
    }

    return *this;
}

void Entity::add_NoPoitner(Entity& entity)
{
    entity.setRemove();
    Entities.push_back(&entity);
}// Define a mutex for the Collisions vector

void Entity::Collision(std::string direction)
{
    rect = Rect(rect.x, rect.y, rect.w, rect.h);
    for (int i = 0; i < Collisions.size(); ++i) {
        if (!rect.checkCollide(Collisions[i]))
            continue;
        if (direction == "y") {

            if (rect.bottom >= Collisions[i].top && old_rect.bottom <= Collisions[i].top) {
                rect.y += Collisions[i].top - rect.bottom;
                rect.bottom = Collisions[i].top;
                isOnGround = true;
            }

            if (rect.top <= Collisions[i].bottom && rect.top >= Collisions[i].bottom) {
                rect.y += Collisions[i].bottom - rect.top;
                rect.top = Collisions[i].bottom;
            }

            velocity.y = 0;
        }
        else {
            if (rect.right >= Collisions[i].left && old_rect.right <= Collisions[i].left) {
                rect.x += Collisions[i].left - rect.right;
                rect.right = Collisions[i].left;
            }

            if (rect.left <= Collisions[i].right && old_rect.left >= Collisions[i].right) {
                rect.x += Collisions[i].right - rect.left;
                rect.left = Collisions[i].right;
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

