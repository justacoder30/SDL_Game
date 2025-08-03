#include "EntityManager.h"
#include "Input.h"
#include "Sprite.h"
#include "Coin.h"
#include "Heart.h"
#include "ButtonText.h"
#include "SoundManager.h"
#include <thread>

void EntityManager::addObjects()
{
	std::string objects_pos[] = {"PlayerPosition", "CoinPosition", "EnemyPosition", "HeartPosition", "FlagPosition", "BossPosition", };

	
	add(
		new Background(
			Vector(Global.camera.rect.w, Global.camera.rect.h)
		)
	);
	add(map);
	player = new Player(0, Vector(0, 0));
	for (auto obj : objects_pos) {
		auto positions = map->GetObjectGroup(obj);

		if (positions.empty()) continue;

		if (obj == "PlayerPosition") {
			for (auto pos : positions) {
				player->rect = Rect(Vector(pos.x, pos.y), Vector(player->rect.w, player->rect.h));
				player->center_pos = player->GetCenter();
				player->SetMapRect(Rect(0, 0, map->getWidth(), map->getHeight()));
				add(player);
			}
		}
		else if (obj == "EnemyPosition") {
			for (auto pos : positions) {
				add(new Enemy(0, Vector(pos.x, pos.y), player));
			}
		}
		else if (obj == "CoinPosition") {
			for (auto pos : positions) {
				add(new Coin(Vector(pos.x, pos.y), player));
			}
		}
		else if (obj == "HeartPosition") {
			for (auto pos : positions) {
				add(new Heart(Vector(pos.x, pos.y), player));
			}
		}
		else if (obj == "FlagPosition") {
			for (auto pos : positions) {
				flag = new Flag(Vector(pos.x, pos.y), player);
				add(flag);
			}
		}
		else if (obj == "BossPosition") {
			for (auto pos : positions) {
				boss = new Boss(Vector(pos.x, pos.y), player);
				add(boss);
			}
		}

	}

	playerHealthBar = new HealthBar(player, Vector(20, 10), Vector(150, 15));
	playerHealthBar->SetStatic();
	playerHealthBar->SetColor(255, 0, 0);
	add(playerHealthBar);

	ButtonText* text = new ButtonText("The Frost Guardian", Vector(160.00, 336.00), Vector(160.00, 32.00));
	text->SetColor(255, 255, 255);

	bossHealthBar = new HealthBar(boss, Vector(160.00, 368.00), Vector(496.00, 16.00));
	bossHealthBar->SetStatic();
	bossHealthBar->SetColor(0, 255, 255);
	bossHealthBar->add(text);

	//add(bossHealthBar);

	add(new LoadingScreen(Vector(64, 64), 1.5));

	
}

void EntityManager::addCollisions()
{
	Collisions = map->GetObjectGroup("Collision");
}

void EntityManager::setCamera()
{
	Rect size = Global.camera.rect;

	Global.camera.SetAnchor(0.5, 0.5);
	Global.camera.SetBound(
		size.w/2,
		size.h/2,
		map->getWidth() - size.w / 2,
		map->getHeight() - size.h / 2
	);
	Global.camera.Follow(&player->center_pos);
}

void EntityManager::addBossHealthBar()
{
	if(bossHealthBar != nullptr) {
		return;
	}
	ButtonText* text = new ButtonText("The Frost Guardian", Vector(160.00, 336.00), Vector(160.00, 32.00));
	text->SetColor(255, 255, 255);

	bossHealthBar = new HealthBar(boss, Vector(160.00, 368.00), Vector(496.00, 16.00));
	bossHealthBar->SetStatic();
	bossHealthBar->SetColor(0, 255, 255);
	bossHealthBar->add(text);

	add(bossHealthBar);
	text = nullptr; 
	bossHealthBar = nullptr;

	delete text;
	delete bossHealthBar;
}

void EntityManager::loadResources(std::string level)
{
	map = new Map(level);
	/*std::thread addObjectsThread(&EntityManager::addObjects, this);
	std::thread addCollisionsThread(&EntityManager::addCollisions, this);

	addObjectsThread.join();
	addCollisionsThread.join();*/

	addObjects();
	addCollisions();

	backDrop = true;
	setCamera();
	SoundManager::PlayMusic();
}

void EntityManager::addGameLoading()
{
	add(new LoadingScreen(Vector(64, 64), 1.5));
}

EntityManager::EntityManager(std::string level)
{
	this->level = level;
	/*loadGame = std::thread(&EntityManager::loadResources, this, level);
	loadGame.join();*/
	/*Global.pool.enqueue([this, level]() {
		this->loadResources(level);
	});*/
	//Global.pool.wait();
	//LOG(Collisions.size());

	loadResources(level);
}

bool EntityManager::LoseGame() {
	return player->isDeath;
}

void EntityManager::watForInit()
{
	loadGame = std::thread(&EntityManager::loadResources, this, level);
	loadGame.join();
}

void EntityManager::Update(const float& dt)
{
	static Rect rect = Global.camera.rect;
	float speed = 7;

	if (Key[SDL_SCANCODE_E]) {
		Global.scale += speed * dt;
	} 

	if (Key[SDL_SCANCODE_Q]) {
		//Global.scale -= speed * dt;
		if (Global.camera.rect.w < rect.w) Global.scale -= speed * dt;
		else {
			Global.camera.rect = rect;
			Global.scale = window.CaculateScale(rect.w, rect.h);
		}
	}

	
	if (boss) {
		if (boss->current == Death && boss->animationManger.IsDone()) {
			/*ChangeLevel();
			return;*/
			boss->removeFromTree();
		}
		if (boss->isInEnemyZone() && boss->currentHp > 0) {
			//addBossHealthBar();
			add(bossHealthBar);
		}
		//else if (!boss->isInEnemyZone() || boss->currentHp <= 0) bossHealthBar->removeFromTree();
	}

	Entity::Update(dt);
	Global.camera.Update();
}

void EntityManager::Draw() {
	Entity::Draw();
}
