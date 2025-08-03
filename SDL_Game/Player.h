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
	~Player()
	{
		//delete state;
		freeEntities();
		freeAnimations();
		LOG("Player destroyed");
	}
	void SetMapRect(Rect rect);
	void UpdateVelocity();
	void UpdatePosition(const float& dt);
	void UpdateState();
	void Update(const float& dt);
	void Draw();
	bool isOutOfMap();
};
