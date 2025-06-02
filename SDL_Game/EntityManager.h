#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Map.h"
#include "LoadingScreen.h"
#include "Flag.h"
#include "Boss.h"

class EntityManager: public Entity
{
private:
	Player* player;
	Boss* boss;
	LoadingScreen * loading;
	HealthBar* playerHealthBar;
	HealthBar* bossHealthBar;
	Map *map;
	Flag *flag;
	void addObjects();
	void addCollisions();
	void setCamera();

public:
	EntityManager() {}
	EntityManager(std::string level);
	bool LoseGame();
	bool WinGame();
	void Update();
	void Draw();
};

