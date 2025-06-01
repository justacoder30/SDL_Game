#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Map.h"
#include "LoadingScreen.h"
#include "Flag.h"

class EntityManager: public Entity
{
private:
	Player* player;
	LoadingScreen * loading;
	HealthBar* playerHealthBar;
	Map *map;
	Flag *flag;
	void addObjects();
	void addCollisions();
	void setCamera();
public:
	

	EntityManager() {}
	EntityManager(std::string level);
	void Update();
	void Draw();
};

