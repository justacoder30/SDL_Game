#pragma once
#include "CharacterState.h"
#include "Entity.h"

class Player : public Entity
{
private:
public:
	Vector center_pos;
	CharacterState active_state;
	State state = State::Idle;

	Player();
	Player(int level);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateState();
	void UpdateAnimation();
	void Update();
};


class IdleState : public CharacterState
{
public:
	IdleState();
	~IdleState() {}
	void Intput(Player& player);
	void Update(Player& player);
};

class RunState : public CharacterState
{
public:
	RunState();
	~RunState() {}
	void Intput(Player& player);
	void Update(Player& player);
};

