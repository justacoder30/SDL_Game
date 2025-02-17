#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	const bool* currentKey = SDL_GetKeyboardState(NULL);
public:
	

	Player();
	Player(int level);
	void UpdateVelocity();
	void UpdatedGravity();
	void UpdatePosition();
	void UpdateState();
	void UpdateAnimation();
	void Update() override;
};

