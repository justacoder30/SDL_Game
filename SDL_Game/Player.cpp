#include "Player.h"
#include "Input.h"

Player::Player()
{}

Player::Player(int level)
{
	animations = {
		{"Idle", Animation("resource/img/Player/Idle.png", 10, 0.05)},
	    {"Run", Animation("resource/img/Player/Run.png", 10, 0.04)},
		{"Attack", Animation("resource/img/Player/Attack.png", 6, 0.04, true)},
		{"Jump", Animation("resource/img/Player/Jump.png", 3)},
		{"Fall", Animation("resource/img/Player/Fall.png", 3)},
	};

	animationManger = AnimationManager(animations["Run"]);
	tex = animations["Run"].texture;
	pos = Vector(0, 0);
	velocity = Vector(0, 0);
	rect = animationManger.getRect();
	speed = 150;
	gravity = 1000;
	jump = 400;

	texture_width = animationManger.animation.FrameWidth;
	texture_height = animationManger.animation.FrameHeight;
	
	SetCollision(42, 48, 0, 57);

	state = State::Idle;

	center_pos = GetCenter();
}

void Player::UpdateVelocity()
{
	velocity.x = 0;

	
	if (Key[SDL_SCANCODE_SPACE] && !falling)
	{
		velocity.y = -jump;
	}
	if (Key[SDL_SCANCODE_A])
	{
		velocity.x = -speed;
		animationManger.flip = SDL_FLIP_HORIZONTAL;
	}
	if (Key[SDL_SCANCODE_D])
	{
		velocity.x = speed;
		animationManger.flip = SDL_FLIP_NONE;
	}

	if (Key[SDL_SCANCODE_S])
	{
		velocity.y = speed;
	}

	if (Key[SDL_SCANCODE_W])
	{
		velocity.y = -speed;
	}

	if (Key[SDL_SCANCODE_Z])
	{
		Global.scale += 10 * Global.DeltaTime;
	}
	if (Key[SDL_SCANCODE_X])
	{
		Global.scale -= 10 * Global.DeltaTime;
	}

	UpdateGravity();
}

void Player::UpdatePosition()
{
	old_rect = rect;
	pos.x += velocity.x * Global.DeltaTime;
	Collision("x");
	pos.y += velocity.y * Global.DeltaTime;
	Collision("y");
}

void Player::UpdateState()
{
	state = State::Idle;

	if (velocity.y != 0) {
		if (velocity.y > 0) state = State::Fall;
		else state = State::Jump;
	}
	else {
		if (velocity.x != 0) state = State::Run;
		else state = State::Idle;
	}
}

void Player::UpdateAnimation()
{
	animationManger.Update();	

	switch (state) {
		case State::Idle:
			animationManger.Play(animations["Idle"]);
			break;
		case State::Run:
			animationManger.Play(animations["Run"]);
			break;
		case State::Jump:
			animationManger.Play(animations["Jump"]);
			break;
		case State::Fall:
			animationManger.Play(animations["Fall"]);
			break;
		default:
			break;
			// code block
	}
		
}	

void Player::Update()
{
	UpdateVelocity();
	UpdatePosition();
	UpdateState();
	UpdateAnimation();

	center_pos = GetCenter();
}

IdleState::IdleState()
{
	state = State::Idle;
}

void IdleState::Intput(Player& player)
{
	if (Key[SDL_SCANCODE_A])
	{
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
	}
	if (Key[SDL_SCANCODE_D])
	{
		player.velocity.x = player.speed;
		player.animationManger.flip = SDL_FLIP_NONE;
	}
}

void IdleState::Update(Player& player)
{

}

RunState::RunState()
{
	state = State::Run;
}




