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
	void UpdatePosition();
	void UpdateAnimation();
	void Update() override;
	void Draw() override;
};

