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

	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J]) return new Attack1State();

	if (!PreKey[SDL_SCANCODE_F] && Key[SDL_SCANCODE_F]) return new DefendState();

	if (player.isHurt) {
		player.velocity.y = -200;
		return new HurtState();
	}

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

	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J]) return new RunAttackState;

	if (player.isHurt) {
		player.velocity.y = -200;
		return new HurtState();
	}

    return this;
}

IPlayerState* FallState::Update(Player& player)
{
	player.current = Fall;

	if (player.isOnGround) {
		if (player.velocity.x != 0) return new RunState();
		return new IdleState();
	}

	if (player.isHurt) {
		player.velocity.y = -200;
		return new HurtState();
	}

	return this;
}

IPlayerState* JumpState::Update(Player& player)
{
	player.current = Jump;

	if (player.velocity.y >= 0) return new FallState();

	if (player.isHurt) {
		player.velocity.y = -200;
		return new HurtState();
	}

	return this;
}

IPlayerState* Attack1State::Update(Player& player)
{
	player.current = Attack1;
	player.velocity.x = 0;
	player.attackFrame = 4;

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
	player.velocity.x = 0;
	player.attackFrame = 3;

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
	player.velocity.x = 0;
	player.attackFrame = 3;

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

IPlayerState* RunAttackState::Update(Player& player)
{
	player.current = RunAttack;
	player.velocity.x = 0;
	player.attackFrame = 4;

	if (!player.isOnGround)
		return new FallState();

	if (player.velocity.y < 0) {
		return new JumpState();
	}

	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J]) return new Attack1State();

	if (player.animationManger.IsDone()) return new IdleState();

	return this;
}

IPlayerState* DefendState::Update(Player& player)
{
	player.current = Defend;
	player.velocity.x = 0;
	
	if (player.velocity.y < 0) return new JumpState();

	if (Key[SDL_SCANCODE_F]) return this;

	return new IdleState();
}

IPlayerState* ProtectState::Update(Player& player)
{
	player.current = Protect;

	if (player.animationManger.IsDone()) return new IdleState();

	return this;
}

IPlayerState* HurtState::Update(Player& player)
{
	player.current = Hurt;
	player.isHurt = false;
	player.velocity.x = 0;

	if (player.animationManger.IsDone()) return new IdleState();

	return this;
}
