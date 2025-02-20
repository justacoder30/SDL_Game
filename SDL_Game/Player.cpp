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
	
	SetCollision(42, 0, 48, 57);

	center_pos = GetCenter();

	state = new IdleState();

}

void Player::UpdateVelocity()
{
	UpdateGravity();
}

void Player::UpdatePosition()
{
	old_rect = rect;

	pos.x += velocity.x * Global.DeltaTime;
	Collision("x");
	pos.y += velocity.y * Global.DeltaTime;
	Collision("y");

	center_pos = GetCenter();
}

void Player::UpdateState()
{
	state = state->Update(*this);
}

void Player::UpdateAnimation()
{
	animationManger.Update();	

	switch (state->GetState()) {
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
	}
		
}	

void Player::Update()
{
	UpdateState();
	UpdateVelocity();
	UpdatePosition();
	UpdateAnimation();
	
}



