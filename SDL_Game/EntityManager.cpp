#include "EntityManager.h"
#include "Input.h"
#include "Sprite.h"
#include "Coin.h"
#include "Heart.h"


//std::cout<< <<std::endl;

void EntityManager::addObjects()
{
	std::string objects_pos[] = { "PlayerPosition", "CoinPosition", "EnemyPosition", "HeartPosition", "FlagPosition" };

	Entities.push_back(
		new Background(
			Vector(Global.camera.rect.w, Global.camera.rect.h)
		)
	);
	Entities.push_back(map);
	for (auto obj : objects_pos) {
		auto positions = map->GetObjectGroup(obj);

		if (positions.empty()) continue;

		if (obj == "PlayerPosition") {
			for (auto pos : positions) {
				player = new Player(0, Vector(pos.x, pos.y));
				player->SetMapRect(Rect(0, 0, map->getWidth(), map->getHeight()));
				Entities.push_back(player);
			}
		} else if (obj == "EnemyPosition") {
			for (auto pos : positions) {
				Entities.push_back(new Enemy(0, Vector(pos.x, pos.y), player));
			}
		} else if (obj == "CoinPosition") {
			for (auto pos : positions) {
				Entities.push_back(new Coin(Vector(pos.x, pos.y), player));
			}
		} else if (obj == "HeartPosition") {
			for (auto pos : positions) {
				Entities.push_back(new Heart(Vector(pos.x, pos.y), player));
			}
		} else if (obj == "FlagPosition") {
			for (auto pos : positions) {
				flag = new Flag(Vector(pos.x, pos.y), player);
				Entities.push_back(flag);
			}
		}
	}
	playerHealthBar = new HealthBar(player, Vector(20, 10), Vector(150, 15));
	playerHealthBar->SetStatic();
	playerHealthBar->SetColor(255, 0, 0);
	Entities.push_back(playerHealthBar);

	loading = new LoadingScreen(Vector(64, 64), 1.5);
	Entities.push_back(loading);
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

EntityManager::EntityManager(std::string level)
{
	map = new Map(level);
	addObjects();
	addCollisions();

	backDrop = true;
	setCamera();
}

void EntityManager::Update()
{
	/*static float scale = Global.scale;
	float speed = 10;

	if (Key[SDL_SCANCODE_E]) {
		Global.scale += speed * Global.DeltaTime;
	}

	if (Key[SDL_SCANCODE_Q]) {
		Global.scale -= speed * Global.DeltaTime;
		if (Global.scale < scale) Global.scale = scale;
	}*/

	loading->Update();
	if (!loading->isEnd()) return;

	Entity::Update();

	Global.camera.Update();
}

void EntityManager::Draw() {
	Entity::Draw();
}
