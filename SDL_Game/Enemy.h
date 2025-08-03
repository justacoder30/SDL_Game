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
	HealthBar* bar;
	void addHealthBar();
	
public:
	Player* player;
	IEnemyState* state;
	double timer = 0;
	double timeChangeState = 3;

	Enemy();
	Enemy(int level, Vector pos, Player* player);
	~Enemy() {
		/*if (bar != nullptr) delete bar;
		if (state != nullptr) delete state;*/
		freeEntities();
		freeAnimations();
		LOG("Enemy destroyed");
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

