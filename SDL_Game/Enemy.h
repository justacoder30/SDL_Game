#pragma once
#include "Entity.h"
#include "IEnemyState.h"
#include "Player.h"

class IEnemyState;

class Enemy : public Entity
{
private:
	Rect edgeRect;
	Player* player;
	
public:
	IEnemyState* state;
	double timer = 0;
	double timeChangeState = 3;

	Enemy();
	Enemy(int level, Vector pos, Player* player);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateState();
	void Update();
	bool isEdge();
	void CollideWithPlayer();

};

