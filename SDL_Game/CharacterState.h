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
