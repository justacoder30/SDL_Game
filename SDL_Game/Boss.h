#pragma once
#include "Entity.h"
#include "Player.h"
#include "HealthBar.h"
#include "IBossState.h"

class IBossState;

class Boss : public Entity
{
private:
	Rect edgeRect;
	float enemyZone = 400;
	HealthBar* bar;

public:
	Player* player;
	IBossState* state;
	int hurtCnt = 0;

	Boss();
	Boss(Vector pos, Player* player);
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

