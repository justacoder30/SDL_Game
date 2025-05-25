#include "Enemy.h"

Enemy::Enemy(int level, Vector pos)
{
	animations = {
		{Idle, Animation("resource/img/Enemy/Skeleton/Idle.png", 8, 0.08)},
		{Run, Animation("resource/img/Enemy/Skeleton/Walk.png", 10, 0.08)},
		{Attack, Animation("resource/img/Enemy/Skeleton/Attack.png", 10, 0.1, false)},
		{Death, Animation("resource/img/Enemy/Skeleton/Death.png", 13, 0.08, false)},
		{Hurt, Animation("resource/img/Enemy/Skeleton/Hurt.png", 5, 0.08, false)},
	};

	animationManger = AnimationManager(animations[Idle]);
	tex = animations[Idle].texture;
	moveSpeed = 200;
	gravity = 800;
	damage = 10;

	current = Idle;

	texture_width = animationManger.animation.FrameWidth;
	texture_height = animationManger.animation.FrameHeight;

	SetCollision(40, 16, 40, 0);

	center_pos = GetCenter();

	//state = new IdleState();

	rect = Rect(
		pos.x,
		pos.y,
		texture_width - OFFSET.left - OFFSET.right, 
		texture_height - OFFSET.top - OFFSET.bottom
	);
	old_rect = rect;
}

void Enemy::UpdateVelocity()
{
	velocity.x = 0;
}

void Enemy::UpdatePosition()
{
	old_rect = rect;

	rect.x += velocity.x * Global.DeltaTime;
	Collision("x");
	rect.y += velocity.y * Global.DeltaTime + gravity * Global.DeltaTime * Global.DeltaTime;
	velocity.y += gravity * Global.DeltaTime;
	Collision("y");

	center_pos = GetCenter();
}

void Enemy::UpdateState()
{

}

void Enemy::Update()
{
	UpdateVelocity();
	UpdateState();
	UpdatePosition();
	UpdateAnimation();
}
