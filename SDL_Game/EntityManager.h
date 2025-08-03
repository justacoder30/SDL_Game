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
	std::thread loadGame;
	std::string level;
	Player *player;
	Boss* boss;
	HealthBar* playerHealthBar;
	HealthBar *bossHealthBar;
	Map *map;
	Flag *flag;
	void addObjects();
	void addCollisions();
	void setCamera();
	void addBossHealthBar();
	void loadResources(std::string level);
	void addGameLoading();

public:
	EntityManager() {}
	EntityManager(std::string level);
	~EntityManager() {
		/*delete map;
		delete boss;
		delete playerHealthBar;
		delete bossHealthBar;
		delete flag;*/
		freeEntities();
		LOG("EntityManager destroyed");	
	}
	bool LoseGame();
	bool WinGame();
	void watForInit();
	void Update(const float& dt);
	void Draw();
};

