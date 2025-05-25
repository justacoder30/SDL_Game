#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Map.h"

class EntityManager
{
private:
	Player* player;
	Map map;
	void addObjects();
	void addCollisions();
	void setCamera();
public:
	std::vector<Entity*> Entities;

	EntityManager() {}
	EntityManager(int level);
	void Update();
	void Draw();
};

