#include "Player.h"
#include "Input.h"

Player::Player()
{}

Player::Player(int level)
{
	animations = {
		{"Idle", Animation("resource/img/Player/Idle.png", 10, 0.05)},
	    {"Run", Animation("resource/img/Player/Run.png", 10, 0.04)},
		{"Attack", Animation("resource/img/Player/Attack.png", 4, 0.065)},
		{"DoubleAttack", Animation("resource/img/Player/Attack2.png", 6, 0.045)},
		{"Jump", Animation("resource/img/Player/Jump.png", 3)},
		{"Fall", Animation("resource/img/Player/Fall.png", 3)},
		{"TurnAround", Animation("resource/img/Player/TurnAround.png", 3)},
		{"Slide", Animation("resource/img/Player/Slide.png", 4)},
		{"Crouch", Animation("resource/img/Player/Crouch.png", 1)},
		{"CrouchTransition", Animation("resource/img/Player/CrouchTransition.png", 1)},
		{"CrouchWalk", Animation("resource/img/Player/CrouchWalk.png", 8)},
		{"CrouchAttack", Animation("resource/img/Player/CrouchAttack.png", 4)},
	};

	animationManger = AnimationManager(animations["Run"]);
	tex = animations["Run"].texture;
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

	rect = Rect(0, 0, texture_width - OFFSET.left - OFFSET.right, texture_height - OFFSET.top - OFFSET.bottom);
	old_rect = rect;

}

void Player::UpdateVelocity()
{
	UpdateGravity();
}

void Player::UpdatePosition()
{
	old_rect = rect;

	rect.x += velocity.x * Global.DeltaTime;
	Collision("x");
	rect.y += velocity.y * Global.DeltaTime;
	Collision("y");

	center_pos = GetCenter();
}

void Player::UpdateState()
{
	state = state->Update(*this);
}

void Player::UpdateAnimation()
{
		

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
		case State::Attack:
			animationManger.Play(animations["Attack"]);
			break;
		case State::DoubleAttack:
			animationManger.Play(animations["DoubleAttack"]);
			break;
		case State::TurnAround:
			animationManger.Play(animations["TurnAround"]);
			break;
		case State::Slide:
			animationManger.Play(animations["Slide"]);
			break;
		case State::Crouch:
			animationManger.Play(animations["Crouch"]);
			break;
		case State::CrouchTransition:
			animationManger.Play(animations["CrouchTransition"]);
			break;
		case State::CrouchWalk:
			animationManger.Play(animations["CrouchWalk"]);
			break;
		case State::CrouchAttack:
			animationManger.Play(animations["CrouchAttack"]);
			break;
		default:
			break;
	}

	animationManger.Update();
		
}	

void Player::Update()
{
	UpdateState();
	UpdateVelocity();
	UpdatePosition();
	UpdateAnimation();
	
}



