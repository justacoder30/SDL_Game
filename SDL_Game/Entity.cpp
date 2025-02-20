#include "Entity.h"

bool Entity::IsFalling()
{
    Rect g_rect = GravityRect();
    for (int i = 0; i < Collisions.size(); ++i) {
        Rect r = Collisions[i]->GetRect();
        /*if (g_rect.checkCollide(r))
            return false;*/
        if (g_rect.top <= r.bottom and
            g_rect.bottom >= r.top and
            g_rect.left <= r.right and
            g_rect.right >= r.left)
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
                pos + Global.camera.current_pos, 
                animationManger.getRect(), 
                animationManger.flip
    );    
}

void Entity::Collision(std::string direction)
{
    rect = GetRect();

    for (int i = 0; i < Collisions.size(); ++i) {
        if (!rect.checkCollide(Collisions[i]->rect))
            continue;
        if (direction == "y") {

            if (rect.bottom >= Collisions[i]->rect.top && old_rect.bottom <= Collisions[i]->old_rect.top) {
                rect.bottom = Collisions[i]->rect.top;
                pos.y = Collisions[i]->rect.top - texture_height + OFFSET.bottom;
                falling = false;
            }

            if (rect.top <= Collisions[i]->rect.bottom && old_rect.top >= Collisions[i]->old_rect.bottom) {
                rect.top = Collisions[i]->rect.bottom;
                pos.y = Collisions[i]->rect.bottom - OFFSET.top;
            }

            velocity.y = 0;
        }
        else {
            if (rect.right >= Collisions[i]->rect.left && old_rect.right <= Collisions[i]->old_rect.left) {
                rect.right = Collisions[i]->rect.left;
                pos.x = Collisions[i]->rect.left - texture_width + OFFSET.right;
            }
            
            if (rect.left <= Collisions[i]->rect.right && old_rect.left >= Collisions[i]->old_rect.right) {
                rect.left = Collisions[i]->rect.right;
                pos.x = Collisions[i]->rect.right - OFFSET.right;
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

Rect Entity::GetRect()
{
    float x = animationManger.IsFlip() != SDL_FLIP_NONE ? pos.x + OFFSET.right : pos.x + OFFSET.left;
    
    return Rect(x,
        pos.y + OFFSET.top,
        texture_width - OFFSET.left - OFFSET.right,
        texture_height - OFFSET.top - OFFSET.bottom);
}

Rect Entity::GravityRect()
{
    float x = animationManger.IsFlip() != SDL_FLIP_NONE ? pos.x + OFFSET.right : pos.x + OFFSET.left;

    return Rect(x,
        pos.y + texture_height - OFFSET.bottom,
        texture_width - OFFSET.left - OFFSET.right,
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