#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
public:
	Vector center_pos;

	Player();
	Player(int level);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateState();
	void UpdateAnimation();
	void Update();
	void Draw();
};

