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
		//{Jump, Animation("resource/img/Knight/Jump1.png", 6, 0.2, false)},
		{Attack1, Animation("resource/img/Knight/Attack 1.png", 5, 0.1, false)},
		{Attack2, Animation("resource/img/Knight/Attack 2.png", 4, 0.1, false)},
		{Attack3, Animation("resource/img/Knight/Attack 3.png", 4, 0.1, false)},
		{RunAttack, Animation("resource/img/Knight/Run+Attack.png", 6, 0.1, false)},
		{Defend, Animation("resource/img/Knight/Defend.png", 5, 0.1)},
		{Protect, Animation("resource/img/Knight/Protect.png", 5, 0.2, false)},
		{Hurt, Animation("resource/img/Knight/Hurt.png", 2, 0.2, false)},
		{Death, Animation("resource/img/Knight/Dead.png", 6, 0.1, false)},
	};

	animationManger = AnimationManager(animations[Idle]);
	tex = animations[Idle].texture;
	moveSpeed = 200;
	gravity = 800;
	jump = 400;
	current = Idle;

	texture_width = animationManger.animation.FrameWidth;
	texture_height = animationManger.animation.FrameHeight;
	
	SetCollision(21, 64, 85, 0);

	center_pos = GetCenter();

	state = new IdleState();

	rect = Rect(
		pos.x,
		pos.y,
		texture_width - OFFSET.left - OFFSET.right,
		texture_height - OFFSET.top - OFFSET.bottom
	);
	old_rect = rect;

	backDrop = true;

	atkBox.left = 57;
	atkBox.top = 74;
	atkBox.right = 19;
	atkBox.bottom = 0;

	atkBox = Rect(
		Vector(57, 54),
		Vector(52, 74)
	);

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

	if (!PreKey[SDL_SCANCODE_SPACE] && Key[SDL_SCANCODE_SPACE] && isOnGround) {
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





