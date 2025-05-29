#include "Enemy.h"


Enemy::Enemy(int level, Vector pos, Player* player)
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
	moveSpeed = 80;
	gravity = 800;
	damage = 10;

	current = Idle;

	texture_width = animationManger.animation.FrameWidth;
	texture_height = animationManger.animation.FrameHeight;

	SetCollision(40, 16, 40, 0);

	center_pos = GetCenter();

	state = new IdleEnemyState();

	rect = Rect(
		pos.x,
		pos.y,
		texture_width - OFFSET.left - OFFSET.right, 
		texture_height - OFFSET.top - OFFSET.bottom
	);
	old_rect = rect;

	damage = 10;

	int min = 2;
	int max = 6;

	timeChangeState = min + std::rand() % (max - min + 1);
	
	this->player = player;
}

void Enemy::UpdateVelocity()
{
	if (velocity.x > 0) {
		animationManger.flip = SDL_FLIP_NONE;
	}
	if (velocity.x < 0) {
		animationManger.flip = SDL_FLIP_HORIZONTAL;
	}
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
	state = state->Update(*this);
}

void Enemy::Update()
{
	UpdateVelocity();
	UpdateState();
	UpdatePosition();
	UpdateAnimation();
	CollideWithPlayer();
}

void Enemy::Draw()
{
	Entity::DrawAnimateGroup();
}

bool Enemy::isEdge()
{
	Rect edgeRect;
	if (!animationManger.IsFlip()) edgeRect = Rect(rect.right, rect.bottom, 2, 2);
	else edgeRect = Rect(rect.left - 2, rect.bottom, 2, 2);

	for (int i = 0; i < Collisions.size(); ++i) {
		if (edgeRect.checkCollide(Collisions[i]))
			return false;
	}

	return true;
}

void Enemy::CollideWithPlayer()
{
	if (rect.checkCollide(player->rect)) {
		player->isHurt = true;
		player->damageTaken = damage;
	}

	if(rect.checkCollide(player->getAtkBox()) && player->isAttacking()) removeFromTree();
}
