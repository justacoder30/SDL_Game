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

	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J]) {
		SoundManager::PlaySoundEffect("attack");
		return new Attack1State();
	}

	if (!PreKey[SDL_SCANCODE_F] && Key[SDL_SCANCODE_F]) return new DefendState();

	if (player.isHurt) {
		player.beingHurt();
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

	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J]) {
		SoundManager::PlaySoundEffect("attack");
		return new RunAttackState;
	}

	if (player.isHurt) {
		player.beingHurt();
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
		player.beingHurt();
		return new HurtState();
	}

	return this;
}

IPlayerState* JumpState::Update(Player& player)
{
	player.current = Jump;

	if (player.velocity.y >= 0) return new FallState();

	if (player.isHurt) {
		player.beingHurt();
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

	if (player.isHurt) {
		player.beingHurt();
		return new HurtState();
	}


	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J])
		comboAtk = true;

	if (player.animationManger.IsDone()) {
		if (comboAtk) {
			SoundManager::PlaySoundEffect("attack");
			return new Attack2State();
		} 
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

	if (player.isHurt) {
		player.beingHurt();
		return new HurtState();
	}

	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J])
		comboAtk = true;

	if (player.animationManger.IsDone()) {
		if (comboAtk) {
			SoundManager::PlaySoundEffect("attack");
			return new Attack3State();
		}  
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

	if (player.isHurt) {
		player.beingHurt();
		return new HurtState();
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

	if (player.isHurt) {
		player.beingHurt();
		return new HurtState();
	}

	if (!PreKey[SDL_SCANCODE_J] && Key[SDL_SCANCODE_J]) comboAtk = true;

	if (player.animationManger.IsDone()) {
		if (comboAtk) {
			SoundManager::PlaySoundEffect("attack");
			return new Attack1State();
		}
		return new IdleState();
	}

	return this;
}

IPlayerState* DefendState::Update(Player& player)
{
	player.current = Defend;
	player.velocity.x = 0;
	
	if (player.isHurt) {
		if(player.animationManger.IsFlip() && player.hurtDirection == 1 ||
			!player.animationManger.IsFlip() && player.hurtDirection == -1
			)
			return new ProtectState();
		else {
			player.beingHurt();
			return new HurtState();
		}
	}

	if (player.velocity.y < 0) return new JumpState();

	if (Key[SDL_SCANCODE_F]) return this;

	return new IdleState();
}

IPlayerState* ProtectState::Update(Player& player)
{
	player.current = Protect;
	player.velocity.x = player.moveSpeed * player.hurtDirection;
	player.isHurt = false;

	if (player.animationManger.IsDone()) {
		if (Key[SDL_SCANCODE_F]) return new DefendState();
		return new IdleState();
	}

	return this;
}

IPlayerState* HurtState::Update(Player& player)
{
	player.current = Hurt;
	player.isHurt = false;
	player.velocity.x = player.moveSpeed/2 * player.hurtDirection;

	/*if (player.animationManger.IsDone()) {
		if (player.currentHp <= 0) return new DeathState();
		return new IdleState();
	}*/

	if (player.isOnGround && player.animationManger.IsDone()) {
		if (player.currentHp <= 0) return new DeathState();
		return new IdleState();
	}


	return this;
}

IPlayerState* DeathState::Update(Player& player)
{
	player.current = Death;

	player.velocity.x = 0;
	if (player.animationManger.IsDone()) {
		SoundManager::StopMusic();
		player.isDeath = true;
	}

	return this;
}
