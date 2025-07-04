#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
#include "Map.h"
#include "LoadingScreen.h"
#include "Flag.h"
#include "Boss.h"
#include <future>

class EntityManager: public Entity
{
private:
	std::future<void> initFuture;
	Player player;
	Boss* boss;
	HealthBar* playerHealthBar;
	HealthBar *bossHealthBar;
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
	void WaitForInit();
	void Update();
	void Draw();
};

