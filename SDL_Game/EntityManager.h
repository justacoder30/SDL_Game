#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Map.h"

class EntityManager
{
private:
	Player* player;
	void addObjects();
public:
	std::vector<Entity*> Entities;

	EntityManager() {}
	EntityManager(int level);
	void Update();
	void Draw();
};

