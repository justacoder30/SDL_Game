#pragma once
#include "Player.h"
#include "Background.h"
#include "Map.h"

class EntityManager
{
private:
	Player* player;
public:
	std::vector<Entity*> Entities;

	EntityManager() {}
	EntityManager(int level);
	void Update();
	void Draw();
};

