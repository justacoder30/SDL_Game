#include "Entity.h"

bool Entity::IsFalling()
{
    Rect g_rect = GravityRect();
    for (int i = 0; i < Collisions.size(); ++i) {
        if (g_rect.checkCollide(Collisions[i]->GetRect()))
            return false;
    }
    return true;
}

void Entity::UpdateGravity()
{
    if (IsFalling())
        velocity.y += gravity * Global.DeltaTime;
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
        std::cout << "Is Collide" << std::endl;
        if (direction == "y") {
            /*if (rect.right >= Collisions[i]->rect.left && old_rect.right <= Collisions[i]->old_rect.left) {
                rect.right = Collisions[i]->rect.left;
                pos.x = Collisions[i]->rect.left - texture_width + OFFSET.right;
            }

            if (rect.left < Collisions[i]->rect.right && old_rect.left > Collisions[i]->old_rect.right) {
                rect.left = Collisions[i]->rect.right;
                pos.x = Collisions[i]->rect.right - OFFSET.left;
            }*/
        }
        else {
            if (rect.right >= Collisions[i]->rect.left && old_rect.right <= Collisions[i]->old_rect.left) {
                rect.right = Collisions[i]->rect.left;
                pos.x = Collisions[i]->rect.left - texture_width + OFFSET.right;
            }
            
            if (rect.left <= Collisions[i]->rect.right && old_rect.left >= Collisions[i]->old_rect.right) {
                rect.left = Collisions[i]->rect.right;
                pos.x = Collisions[i]->rect.right - OFFSET.left;
            }
        }
    }
}

void Entity::SetCollision(float _top, float _left, float _bottom, float _right)
{
    OFFSET.top = _top;
    OFFSET.left = _left;
    OFFSET.bottom = _bottom;
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