#include "Enemy.h"


Enemy::Enemy(int level, Vector pos, Player* player)
{
	animations = {
		{Idle, Animation("resource/img/Enemy/Skeleton/Idle.png", 8, 0.08)},
		{Run, Animation("resource/img/Enemy/Skeleton/Walk.png", 10, 0.08)},
		{Attack, Animation("resource/img/Enemy/Skeleton/Attack.png", 10, 0.1)},
		{Death, Animation("resource/img/Enemy/Skeleton/Death.png", 13, 0.08, false)},
		{Hurt, Animation("resource/img/Enemy/Skeleton/Hurt.png", 5, 0.07, false)},
	};

	animationManger = AnimationManager(animations[Idle]);
	tex = animations[Idle].texture;
	moveSpeed = 80;
	gravity = 800;
	damage = 20;
	hp = 40;
	currentHp = hp;

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

	atkBox = Rect(
		Vector(54, 18),
		Vector(40, 30)
	);

	bar = new HealthBar(this, Vector(20, 8), Vector(50, 5));
	bar->SetColor(0, 255, 0);
	bar->SetErase();
	
}

void Enemy::UpdateVelocity()
{
	if (current == Hurt || current == Death) return;
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
	Entity::Update();
	CollideWithPlayer();
	UpdateVelocity();
	UpdateState();
	UpdatePosition();
	UpdateAnimation();

	
}

void Enemy::Draw()
{
	Entity::DrawAnimateGroup();
	Entity::Draw();
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

bool Enemy::isHitWall()
{
	float x = animationManger.IsFlip() ? rect.x - 2 : rect.x + rect.w;
	Rect wall_rect = Rect(x, rect.y, 2, rect.h);

	for (int i = 0; i < Collisions.size(); ++i) {
		if (wall_rect.checkCollide(Collisions[i]))
			return true;
	}

	return false;
}

bool Enemy::isInEnemyZone()
{
	float distance = sqrt(pow(center_pos.x - player->center_pos.x, 2) + pow(center_pos.y - player->center_pos.y, 2));
	return distance <= enemyZone && player->current != Death;
}

bool Enemy::isInAttackZone()
{
	return player->rect.checkCollide(getAtkBox());
}

bool Enemy::checkTurn()
{
	float d = center_pos.x - player->center_pos.x;
	if (animationManger.IsFlip() && d < 0) return true;
	else if (!animationManger.IsFlip() && d > 0) return true;
	return false;
}

void Enemy::CollideWithPlayer()
{
	if (rect.checkCollide(player->rect) && current != Death) {
		player->beingAttacked(*this);
	}

	if (rect.checkCollide(player->getAtkBox()) && player->isAttacking()) {
		bar->resetTime();
		beingAttacked(*player);
		if(isHurt) add(bar);
	}

	if (player->rect.checkCollide(getAtkBox()) && isAttacking()) {
		player->beingAttacked(*this);
	}
}
