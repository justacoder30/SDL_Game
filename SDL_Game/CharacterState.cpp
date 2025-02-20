#include "CharacterState.h"
#include "Input.h"

CharacterState* CharacterState::Update(Player& player)
{
	return nullptr;
}

IdleState::IdleState()
{
	state = State::Idle;
}

CharacterState* IdleState::Update(Player& player)
{
	player.velocity.x = 0;

	if (Key[SDL_SCANCODE_SPACE] && !player.falling)
	{
		player.velocity.y = -player.jump;
		return new JumpState();
	}

	if (player.falling)
	{
		return new FallState();
	}

	if (Key[SDL_SCANCODE_A])
	{
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
		return new RunState();
	}
	if (Key[SDL_SCANCODE_D])
	{
		player.velocity.x = player.speed;
		player.animationManger.flip = SDL_FLIP_NONE;
		return new RunState();
	}

    return new IdleState();
}

RunState::RunState()
{
	state = State::Run;
}

CharacterState* RunState::Update(Player& player)
{
	if (Key[SDL_SCANCODE_SPACE] && !player.falling)
	{
		player.velocity.y = -player.jump;
		return new JumpState();
	}

	if (player.falling)
	{
		return new FallState();
	}

	if (Key[SDL_SCANCODE_A])
	{
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
		return new RunState();
	}

	if (Key[SDL_SCANCODE_D])
	{
		player.velocity.x = player.speed;
		player.animationManger.flip = SDL_FLIP_NONE;
		return new RunState();
	}	

	return new IdleState();
}

JumpState::JumpState()
{
	state = State::Jump;
}

CharacterState* JumpState::Update(Player& player)
{
	player.velocity.x = 0;

	if (Key[SDL_SCANCODE_A])
	{
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
	} 
	else if (Key[SDL_SCANCODE_D])
	{
		player.velocity.x = player.speed;
		player.animationManger.flip = SDL_FLIP_NONE;
	}
	if (player.velocity.y > 0)
		return new FallState();
	return new JumpState();
}

FallState::FallState()
{
	state = State::Fall;
}

CharacterState* FallState::Update(Player& player)
{
	player.velocity.x = 0;

	if (Key[SDL_SCANCODE_A])
	{
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
	}
	else if (Key[SDL_SCANCODE_D])
	{
		player.velocity.x = player.speed;
		player.animationManger.flip = SDL_FLIP_NONE;
	}
	if (player.velocity.y < 0)
		return new JumpState();
	if (player.velocity.y == 0)
		return new IdleState();
	return new FallState();
}
