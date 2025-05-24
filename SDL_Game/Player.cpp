#include "Player.h"
#include "Input.h"

Player::Player()
{}

Player::Player(int level, Vector pos)
{
	animations = {
		{Idle, Animation("resource/img/Knight/Idle.png", 4, 0.17)},
		{Run, Animation("resource/img/Knight/Run.png", 7, 0.09)},
		{Fall, Animation("resource/img/Knight/Fall.png", 4, 0.135, false)},
		{Jump, Animation("resource/img/Knight/Jump.png", 2, 0.12, false)},
		{Hurt, Animation("resource/img/Knight/Hurt.png", 2, 0.2, false)},
		{Death, Animation("resource/img/Knight/Dead.png", 6, 0.1, false)},
		{Death, Animation("resource/img/Knight/Dead.png", 6, 0.1, false)},
		{Death, Animation("resource/img/Knight/Dead.png", 6, 0.1, false)},
	};

	animationManger = AnimationManager(animations[Idle]);
	tex = animations[Idle].texture;
	velocity = Vector(0, 0);
	rect = animationManger.getRect();
	moveSpeed = 200;
	gravity = 800;
	jump = 400;
	current = Run;

	texture_width = animationManger.animation.FrameWidth;
	texture_height = animationManger.animation.FrameHeight;
	
	SetCollision(21, 64, 85, 0);

	center_pos = GetCenter();

	state = new IdleState();

	rect = Rect(pos.x + OFFSET.left, pos.y - OFFSET.top, texture_width - OFFSET.left - OFFSET.right, texture_height - OFFSET.top - OFFSET.bottom);
	old_rect = rect;

}

void Player::UpdateVelocity()
{
	UpdateGravity();

	velocity.x = 0;

	if (Key[SDL_SCANCODE_A]) {
		velocity.x = -moveSpeed;
		animationManger.flip = SDL_FLIP_HORIZONTAL;
	}

	if (Key[SDL_SCANCODE_D]) {
		velocity.x = moveSpeed;
		animationManger.flip = SDL_FLIP_NONE;
	}

	if (Key[SDL_SCANCODE_SPACE] && isOnGround) {
		velocity.y = -jump;
	}
}

void Player::UpdatePosition()
{
	old_rect = rect;

	rect.x += velocity.x * Global.DeltaTime;
	Collision("x");
	rect.y += velocity.y * Global.DeltaTime + gravity * Global.DeltaTime * Global.DeltaTime;
	velocity.y += gravity * Global.DeltaTime;
	Collision("y");

	center_pos = GetCenter();
}

void Player::UpdateState()
{
	state = state->Update(*this);
}

void Player::Update()
{
	UpdateVelocity();
	UpdateState();
	UpdatePosition();
	UpdateAnimation();
}





