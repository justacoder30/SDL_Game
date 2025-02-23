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

	if (Key[SDL_SCANCODE_SPACE] && !player.falling)	{
		player.velocity.y = -player.jump;
		return new JumpState();
	}

	if (player.falling)	
		return new FallState();	

	if (Key[SDL_SCANCODE_LCTRL] && !PrevKey[SDL_SCANCODE_LCTRL])
		return new CrouchTransitionState(true);

	if (Key[SDL_SCANCODE_J] && !PrevKey[SDL_SCANCODE_J]) 
		return new AttackState();

	if (Key[SDL_SCANCODE_A]) {
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
		return new RunState();
	}

	if (Key[SDL_SCANCODE_D]) {
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
	if (Key[SDL_SCANCODE_SPACE] && !player.falling)	{
		player.velocity.y = -player.jump;
		return new JumpState();
	}

	if (player.falling)	{
		return new FallState();
	}

	if (Key[SDL_SCANCODE_A] && Key[SDL_SCANCODE_S] && !PrevKey[SDL_SCANCODE_S]) {
		return new SlideState();
	}

	if (Key[SDL_SCANCODE_D] && Key[SDL_SCANCODE_S] && !PrevKey[SDL_SCANCODE_S]) {
		return new SlideState();
	}

	if (Key[SDL_SCANCODE_A] && !player.animationManger.IsFlip()) {
		return new TurnAroundState();
	}

	if (Key[SDL_SCANCODE_D] && player.animationManger.IsFlip()) {
		return new TurnAroundState();
	}

	if (Key[SDL_SCANCODE_A]) {
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
		return new RunState();
	}

	if (Key[SDL_SCANCODE_D]) {
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

	if (Key[SDL_SCANCODE_A]) {
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
	} 
	else if (Key[SDL_SCANCODE_D]) {
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

	if (Key[SDL_SCANCODE_A]) {
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
	}
	else if (Key[SDL_SCANCODE_D]) {
		player.velocity.x = player.speed;
		player.animationManger.flip = SDL_FLIP_NONE;
	}
	if (player.velocity.y < 0)
		return new JumpState();
	if (player.velocity.y == 0)
		return new IdleState();
	return new FallState();
}

AttackState::AttackState()
{
	state = State::Attack;
	doubleAttack = false;
}

CharacterState* AttackState::Update(Player& player)
{
	if (player.animationManger.FrameEnd() && doubleAttack)
		return new DoubleAttackState();

	if (player.animationManger.FrameEnd())
		return new IdleState();

	if (Key[SDL_SCANCODE_A]) {
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
		return new RunState();
	}

	if (Key[SDL_SCANCODE_D]) {
		player.velocity.x = player.speed;
		player.animationManger.flip = SDL_FLIP_NONE;
		return new RunState();
	}

	if (Key[SDL_SCANCODE_J] && !PrevKey[SDL_SCANCODE_J]) 
		doubleAttack = true;

	return this;
}

DoubleAttackState::DoubleAttackState()
{
	state = State::DoubleAttack;
}

CharacterState* DoubleAttackState::Update(Player& player)
{
	if (player.animationManger.FrameEnd())
		return new IdleState();

	if (Key[SDL_SCANCODE_A]) {
		player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
		return new RunState();
	}

	if (Key[SDL_SCANCODE_D]) {
		player.velocity.x = player.speed;
		player.animationManger.flip = SDL_FLIP_NONE;
		return new RunState();
	}

	return new DoubleAttackState();
}

TurnAroundState::TurnAroundState()
{
	state = State::TurnAround;
}

CharacterState* TurnAroundState::Update(Player& player)
{
	player.velocity.x *= 0.8f;
	if (player.animationManger.FrameEnd()) {
		player.animationManger.flip = player.animationManger.IsFlip() ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
		return new RunState();
	}

	return new TurnAroundState();
}

SlideState::SlideState()
{
	state = State::Slide;
}

CharacterState* SlideState::Update(Player& player)
{
	float boost = 1.8;
	player.velocity.x = (player.velocity.x > 0) ? player.speed * boost : -player.speed * boost;
	if (player.animationManger.FrameEnd())
		return new IdleState();

	if (player.falling)
		return new FallState();

	return new SlideState();
}

CrouchTransitionState::CrouchTransitionState(bool _crouch)
{
	state = State::CrouchTransition;
	crouch = _crouch;
}

CharacterState* CrouchTransitionState::Update(Player& player)
{
	if (!player.animationManger.FrameEnd())
		return this;
	if (crouch)
		return new CrouchState();
	else return new IdleState();
}

CrouchState::CrouchState()
{
	state = State::Crouch;
}

CharacterState* CrouchState::Update(Player& player)
{
	player.velocity.x = 0;
	if (Key[SDL_SCANCODE_LCTRL] && !PrevKey[SDL_SCANCODE_LCTRL])
		return new CrouchTransitionState(false);

	if (Key[SDL_SCANCODE_D]) {
		//player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_NONE;
		return new CrouchWalkState();
	}

	if (Key[SDL_SCANCODE_A]) {
		//player.velocity.x = -player.speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
		return new CrouchWalkState();
	}

	if (Key[SDL_SCANCODE_J] && !PrevKey[SDL_SCANCODE_J])
		return new CrouchAttackState();

	return new CrouchState();
}

CrouchWalkState::CrouchWalkState()
{
	state = State::CrouchWalk;
}

CharacterState* CrouchWalkState::Update(Player& player)
{
	float crouch_speed = player.speed * 0.5;
	if (Key[SDL_SCANCODE_LCTRL] && !PrevKey[SDL_SCANCODE_LCTRL])
		return new CrouchTransitionState(false);

	if (Key[SDL_SCANCODE_A]) {
		player.velocity.x = -crouch_speed;
		player.animationManger.flip = SDL_FLIP_HORIZONTAL;
		return new CrouchWalkState();
	}

	if (Key[SDL_SCANCODE_D]) {
		player.velocity.x = crouch_speed;
		player.animationManger.flip = SDL_FLIP_NONE;
		return new CrouchWalkState();
	}

	return new CrouchState();
}

CrouchAttackState::CrouchAttackState()
{
	state = State::CrouchAttack;
}

CharacterState* CrouchAttackState::Update(Player& player)
{
	if (player.animationManger.FrameEnd())
		return new CrouchState();
	return new CrouchAttackState();
}
