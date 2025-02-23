#pragma once
#include "CharacterState.h"
#include "Entity.h"

class CharacterState;

class Player : public Entity
{
private:
public:
	Vector center_pos;
	CharacterState* state;

	Player();
	Player(int level, Vector pos);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateState();
	void UpdateAnimation();
	void Update();
};
