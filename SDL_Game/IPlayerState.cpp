#include "IPlayerState.h"
#include "Input.h"

IPlayerState* IdleState::Update(Player& player)
{
    player.current = Idle;

	if (!player.isOnGround)
		return new FallState();

	if (player.velocity.y < 0) {
		return new JumpState();
	}
		
	if (player.velocity.x != 0) return new RunState();

	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J])
		return new Attack1State();

    return this;
}

IPlayerState* RunState::Update(Player& player)
{
    player.current = Run;

	if (!player.isOnGround)
		return new FallState();

	if (player.velocity.y < 0) {
		return new JumpState();
	}

	if (player.velocity.x == 0) return new IdleState();

    return this;
}

IPlayerState* FallState::Update(Player& player)
{
	player.current = Fall;

	if (player.isOnGround) {
		if (player.velocity.x != 0) return new RunState();
		return new IdleState();
	}

	return this;
}

IPlayerState* JumpState::Update(Player& player)
{
	player.current = Jump;

	if (player.velocity.y >= 0) return new FallState();

	return this;
}

IPlayerState* Attack1State::Update(Player& player)
{
	player.current = Attack1;

	if (!player.isOnGround)
		return new FallState();

	if (player.velocity.y < 0) {
		return new JumpState();
	}

	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J])
		comboAtk = true;

	if (player.animationManger.IsDone()) {
		if (comboAtk) return new Attack2State();
		return new IdleState();
	}

	return this;
}

IPlayerState* Attack2State::Update(Player& player)
{
	player.current = Attack2;

	if (!player.isOnGround)
		return new FallState();

	if (player.velocity.y < 0) {
		return new JumpState();
	}

	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J])
		comboAtk = true;

	if (player.animationManger.IsDone()) {
		if (comboAtk) return new Attack3State();
		return new IdleState();
	}

	return this;
}

IPlayerState* Attack3State::Update(Player& player)
{
	player.current = Attack3;

	if (!player.isOnGround)
		return new FallState();

	if (player.velocity.y < 0) {
		return new JumpState();
	}

	if (player.animationManger.IsDone()) {
		return new IdleState();
	}

	return this;
}
