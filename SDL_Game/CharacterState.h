#pragma once
#include "Player.h"

class Player;
enum State;

class CharacterState
{
protected:
	State state;
public:
	virtual CharacterState* Update(Player& player);
	State GetState() {
		return state;
	}
};

class IdleState : public CharacterState
{
public:
	IdleState();
	CharacterState* Update(Player& player) override;
};

class RunState : public CharacterState
{
public:
	RunState();
	CharacterState* Update(Player& player) override;
};

class JumpState : public CharacterState
{
public:
	JumpState();
	CharacterState* Update(Player& player) override;
};

class FallState : public CharacterState
{
public:
	FallState();
	CharacterState* Update(Player& player) override;
};

class AttackState : public CharacterState
{
protected:
	bool doubleAttack;
public:
	AttackState();
	CharacterState* Update(Player& player) override;
};

class DoubleAttackState : public CharacterState
{
public:
	DoubleAttackState();
	CharacterState* Update(Player& player) override;
};

class TurnAroundState : public CharacterState
{
public:
	TurnAroundState();
	CharacterState* Update(Player& player) override;
};

class SlideState : public CharacterState
{
public:
	SlideState();
	CharacterState* Update(Player& player) override;
};

class CrouchTransitionState : public CharacterState
{
private:
	bool crouch;
public:
	CrouchTransitionState(bool _crouch);
	CharacterState* Update(Player& player) override;
};

class CrouchState : public CharacterState
{
public:
	CrouchState();
	CharacterState* Update(Player& player) override;
};

class CrouchWalkState : public CharacterState
{
public:
	CrouchWalkState();
	CharacterState* Update(Player& player) override;
};

class CrouchAttackState : public CharacterState
{
public:
	CrouchAttackState();
	CharacterState* Update(Player& player) override;
};

