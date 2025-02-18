#include "Player.h"

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
	flip = SDL_FLIP_NONE;

	texture_width = animationManger.animation.FrameWidth;
	texture_height = animationManger.animation.FrameHeight;
	OFFSET[0] = 52;
	OFFSET[1] = 42;

	state = State::Idle;

	center_pos = GetCenter();
}

void Player::UpdateVelocity()
{
	velocity.x = 0;	

	UpdateGravity();

	if (currentKey[SDL_SCANCODE_SPACE] && !IsFalling())
	{
		velocity.y = -jump;
	}
	if (currentKey[SDL_SCANCODE_A])
	{
		velocity.x = -speed;
		flip = SDL_FLIP_HORIZONTAL;
	}
	if (currentKey[SDL_SCANCODE_D])
	{
		velocity.x = speed;
		flip = SDL_FLIP_NONE;
	}

	if (currentKey[SDL_SCANCODE_Z])
	{
		Global.scale += 10 * Global.DeltaTime;
	}
	if (currentKey[SDL_SCANCODE_X])
	{
		Global.scale -= 10 * Global.DeltaTime;
	}
}

void Player::UpdatePosition()
{
	pos += velocity * Global.DeltaTime;
	rect = GetRect();
	for (int i = 0; i < Collisions.size(); ++i) {
		if (rect.checkCollide(Collisions[i]->GetRect())) {
			velocity.y = 0;
			pos.y = Collisions[i]->GetRect().top - texture_height;
		}
	}
	
	//pos += velocity * Global.DeltaTime;


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

void Player::Draw()
{
	Entity::Draw();
	rect = GetRect();
	Rect gravity = GravityRect();
	Rect r = Rect(rect.x + Global.camera.current_pos.x, rect.y + Global.camera.current_pos.y, rect.w, rect.h);
	Rect g = Rect(gravity.x + Global.camera.current_pos.x, gravity.y + Global.camera.current_pos.y, gravity.w, gravity.h);
	window.DrawRect(r);
	window.DrawRect(g);
}




