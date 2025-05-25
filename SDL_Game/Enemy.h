#pragma once
#include "Entity.h"

class Enemy : public Entity
{
private:
public:
	//IPlayerState* state;

	Enemy();
	Enemy(int level, Vector pos);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateState();
	void Update();
};

