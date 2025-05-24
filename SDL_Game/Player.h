#pragma once
#include "IPlayerState.h"
#include "Entity.h"

class IPlayerState;

class Player : public Entity
{
private:
public:
	IPlayerState* state;

	Player();
	Player(int level, Vector pos);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateState();
	void Update();
};
