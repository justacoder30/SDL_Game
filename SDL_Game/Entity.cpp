#include "Entity.h"

bool Entity::IsFalling()
{
    Rect g_rect = GravityRect();
    for (int i = 0; i < Collisions.size(); ++i) {
        if (g_rect.checkCollide(Collisions[i]->rect))
            return false;
    }
    return true;
}

void Entity::UpdateGravity()
{
    if (IsFalling()) {
        velocity.y += gravity * Global.DeltaTime;
        falling = true;
    }
}

Entity::Entity()
{}

void Entity::Update()
{
}

void Entity::Draw()
{
    window.blit(animationManger.animation.texture, 
                GetPos() + Global.camera.current_pos,
                animationManger.getRect(), 
                animationManger.flip
    );    

    Rect r = rect;
    r.x += Global.camera.current_pos.x;
    r.y += Global.camera.current_pos.y;

    Rect g_rect = GravityRect();
    g_rect.x += Global.camera.current_pos.x;
    g_rect.y += Global.camera.current_pos.y;

    window.DrawRect(r);
    window.DrawRect(g_rect);
}

void Entity::Collision(std::string direction)
{
    rect = Rect(rect.x, rect.y, rect.w, rect.h);

    for (int i = 0; i < Collisions.size(); ++i) {
        if (!rect.checkCollide(Collisions[i]->rect))
            continue;
        if (direction == "y") {

            if (rect.bottom >= Collisions[i]->rect.top && old_rect.bottom <= Collisions[i]->old_rect.top) {
                rect.bottom = Collisions[i]->rect.top;
                rect.y = Collisions[i]->rect.top - rect.h;
                falling = false;
            }

            if (rect.top <= Collisions[i]->rect.bottom && old_rect.top >= Collisions[i]->old_rect.bottom) {
                rect.top = Collisions[i]->rect.bottom;
                rect.y = Collisions[i]->rect.bottom;
            }

            velocity.y = 0;
        }
        else {
            if (rect.right >= Collisions[i]->rect.left && old_rect.right <= Collisions[i]->old_rect.left) {
                rect.right = Collisions[i]->rect.left;
                rect.x = Collisions[i]->rect.left - rect.w;
            }
            
            if (rect.left <= Collisions[i]->rect.right && old_rect.left >= Collisions[i]->old_rect.right) {
                rect.left = Collisions[i]->rect.right;
                rect.x = Collisions[i]->rect.right;
            }
        }
    }
}

void Entity::SetCollision(float _top, float _bottom, float _left, float _right)
{
    OFFSET.top = _top;
    OFFSET.bottom = _bottom;
    OFFSET.left = _left;
    OFFSET.right = _right;
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
        3
    );
}

Vector Entity::GetCenter()
{
    float pos_X = rect.x + (rect.w / 2);
    float pos_Y = rect.y + (rect.h / 2);
    return Vector(pos_X, pos_Y);
}

std::vector<Entity*> Collisions;