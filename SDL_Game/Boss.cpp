#include "Boss.h"

Boss::Boss()
{}

Boss::Boss(Vector pos, Player* player)
{
	//framesize = (384, 256)
	scale = 2;
	animations = {
		{Idle, Animation("resource/img/Enemy/Frost_Guardian/Idle.png", 6, 0.08)},
		{Walk, Animation("resource/img/Enemy/Frost_Guardian/Walk.png", 10, 0.08)},
		{Attack, Animation("resource/img/Enemy/Frost_Guardian/Attack.png", 14, 0.14)},
		{Death, Animation("resource/img/Enemy/Frost_Guardian/Death.png", 16, 0.14, false)},
		{Hurt, Animation("resource/img/Enemy/Frost_Guardian/Hurt.png", 7, 0.06, false)},
	};

	animationManger = AnimationManager(animations[Idle]);
	tex = animations[Idle].texture;
	moveSpeed = 80;
	gravity = 800;
	damage = 20;
	getHitJump = 150;
	//hp = 200;
	hp = 100;
	currentHp = hp;

	texture_width = animationManger.animation.FrameWidth;
	texture_height = animationManger.animation.FrameHeight;

	SetCollision(77 * scale, 36 * scale, 73 * scale, 18 * scale);

	center_pos = GetCenter();

	state = new IdleBossState();

	rect = Rect(
		pos.x,
		pos.y,
		texture_width * scale - OFFSET.left - OFFSET.right,
		texture_height * scale - OFFSET.top - OFFSET.bottom
	);
	old_rect = rect;

	this->player = player;

	atkBox = Rect(
		Vector(5 * scale, 69 * scale),
		Vector(55 * scale, 20 * scale)
	);

	bar = new HealthBar(this, Vector(20 * scale, 8 * scale), Vector(50 * scale, 5 * scale));
	bar->SetColor(0, 255, 255);
	bar->SetErase();

	center_pos = GetCenter();
}

void Boss::UpdateVelocity()
{
	if (current == Hurt || current == Death) return;
	if (velocity.x > 0) {
		animationManger.flip = SDL_FLIP_HORIZONTAL;
	}
	if (velocity.x < 0) {
		animationManger.flip = SDL_FLIP_NONE;
	}
}

void Boss::UpdatePosition(const float& dt)
{
	//old_rect = rect;
	old_rect = Rect(rect.x, rect.y, rect.w, rect.h);

	rect.x += velocity.x * dt;
	Collision("x");
	//rect.y += velocity.y * dt + 0.5 * gravity * dt * dt;
	rect.y += velocity.y * dt;
	if (!IsOnGround()) velocity.y += gravity * dt;
	Collision("y");

	center_pos = GetCenter();
}

void Boss::UpdateState()
{
	if (currentHp <= 0) state = new DeathBossState();
	state = state->Update(*this);
}

void Boss::Update(const float& dt)
{
	UpdateVelocity();
	UpdateState();
	UpdatePosition(dt);
	UpdateAnimation(dt);
	CollideWithPlayer(dt);
	Entity::Update(dt);
}

void Boss::Draw()
{
	DrawAnimateGroup();
	Entity::Draw();
}

bool Boss::isEdge()
{
	if (animationManger.IsFlip()) edgeRect = Rect(rect.right, rect.bottom, 2, 2);
	else edgeRect = Rect(rect.left - 2, rect.bottom, 2, 2);

	for (int i = 0; i < Collisions.size(); ++i) {
		if (edgeRect.checkCollide(Collisions[i]))
			return false;
	}

	return true;
}

bool Boss::isHitWall()
{
	float x = !animationManger.IsFlip() ? rect.x - 2 : rect.x + rect.w;
	Rect wall_rect = Rect(x, rect.y, 2, rect.h);

	for (int i = 0; i < Collisions.size(); ++i) {
		if (wall_rect.checkCollide(Collisions[i]))
			return true;
	}

	return false;
}

bool Boss::isInEnemyZone()
{
	float distance = sqrt(pow(center_pos.x - player->center_pos.x, 2) + pow(center_pos.y - player->center_pos.y, 2));
	return distance <= enemyZone && player->current != Death;
}

bool Boss::isInAttackZone()
{
	return player->rect.checkCollide(getAtkBox());
}

bool Boss::checkTurn()
{
	float d = center_pos.x - player->center_pos.x;
	if (!animationManger.IsFlip() && d < 0) return true;
	else if (animationManger.IsFlip() && d > 0) return true;
	return false;
}

void Boss::CollideWithPlayer(const float& dt)
{
	if (rect.checkCollide(player->rect) && current != Death) {
		player->beingAttacked(*this, dt);
	}

	if (rect.checkCollide(player->getAtkBox()) && player->isAttacking()) {
		beingAttacked(*player, dt);
	}
	if (player->rect.checkCollide(getAtkBox()) && isAttacking()) {
		player->beingAttacked(*this, dt);
	}
}
