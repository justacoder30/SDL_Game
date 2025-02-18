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
                flip
    );
}

Rect Entity::GetRect()
{
    return Rect(pos.x + OFFSET[0],
        pos.y + OFFSET[1],
        texture_width - OFFSET[0] * 2,
        texture_height - OFFSET[1]);
}

Rect Entity::GravityRect()
{
    return Rect(pos.x + OFFSET[0],
        pos.y + texture_height,
        texture_width - OFFSET[0] * 2,
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