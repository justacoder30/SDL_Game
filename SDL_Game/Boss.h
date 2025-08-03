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
	~Boss() {
		/*if (bar != nullptr) delete bar;
		if (state != nullptr) delete state;
		if (player != nullptr) delete player;*/
		freeEntities();
		freeAnimations();
		LOG("Boss destroyed");
	}
	void UpdateVelocity();
	void UpdatePosition(const float& dt);
	void UpdateState();
	void Update(const float& dt);
	void Draw();
	bool isEdge();
	bool isHitWall();
	bool isInEnemyZone();
	bool isInAttackZone();
	bool checkTurn();
	void CollideWithPlayer(const float& dt);
};

