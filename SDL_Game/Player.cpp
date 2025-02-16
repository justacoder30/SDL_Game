#include "Player.h"

Player::Player()
{}

Player::Player(int level)
{
	animations = {
		{"Idle", Animation("resource/img/Player/Idle.png", 10, 0.05)},
	    {"Run", Animation("resource/img/Player/Run.png", 10, 0.04)},
	};

	animationManger = AnimationManager(animations["Run"]);
	tex = animations["Run"].texture;
	pos = Vector(0, 0);
	velocity = Vector(0, 0);
	rect = animationManger.getRect();
	speed = 150;
	flip = SDL_FLIP_NONE;
}

void Player::UpdateVelocity()
{
	velocity = Vector(0, 0);

	if (currentKey[SDL_SCANCODE_W])
	{
		velocity.y = -speed;
	}
	if (currentKey[SDL_SCANCODE_S])
	{
		velocity.y = speed;
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
}

void Player::UpdatePosition()
{
	pos += velocity * Global.DeltaTime;
}

void Player::UpdateAnimation()
{
	animationManger.Update();
	
	if (velocity.x != 0)
		animationManger.Play(animations["Run"]);
	else
		animationManger.Play(animations["Idle"]);
}	

void Player::Update()
{
	UpdateVelocity();
	UpdatePosition();
	UpdateAnimation();
}

void Player::Draw()
{
	window.blit(animationManger.animation.texture, pos + Global.camera.current_pos, animationManger.getRect(), flip);
}


