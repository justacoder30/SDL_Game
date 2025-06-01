#pragma once
#include "Entity.h"
#include "IEnemyState.h"
#include "Player.h"
#include "HealthBar.h"

class IEnemyState;

class Enemy : public Entity
{
private:
	Rect edgeRect;
	
	float enemyZone = 150;
	HealthBar *bar;
	
public:
	Player* player;
	IEnemyState* state;
	double timer = 0;
	double timeChangeState = 3;

	Enemy();
	Enemy(int level, Vector pos, Player* player);
	void UpdateVelocity();
	void UpdatePosition();
	void UpdateState();
	void Update();
	void Draw();
	bool isEdge();
	bool isHitWall();
	bool isInEnemyZone();
	bool isInAttackZone();
	bool checkTurn();
	void CollideWithPlayer();

};

