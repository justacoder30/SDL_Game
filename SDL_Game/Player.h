#pragma once
#include "IPlayerState.h"
#include "Entity.h"

class IPlayerState;

class Player : public Entity
{
private:
	Rect mapRect;
public:
	IPlayerState* state;
	bool isDeath = false;

	Player();
	Player(int level, Vector pos);
	void SetMapRect(Rect rect);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateState();
	void Update();
	void Draw();
	bool isOutOfMap();
};
