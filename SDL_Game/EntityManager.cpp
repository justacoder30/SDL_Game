#include "EntityManager.h"

std::string objects_pos[] = { "PlayerPosition", "CoinPosition", "EnemyPosition", "HeartPosition", "FlagPosition" };
//std::cout<< <<std::endl;

void EntityManager::addObjects()
{
	Entities.push_back(new Background());
	Map map(1, Entities);

	for (auto obj : objects_pos) {
		auto positions = map.GetObjectGroup(obj);

		if (positions.empty()) continue;

		if (obj == "PlayerPosition") {
			for (auto pos : positions) {
				player = new Player(0, Vector(pos.x, pos.y));
				Entities.push_back(player);
			}
		} else if (obj == "EnemyPosition") {
			for (auto pos : positions) {
				Entities.push_back(new Enemy(0, Vector(pos.x, pos.y)));
			}
		}
	}

	
}

EntityManager::EntityManager(int level)
{
	addObjects();

	Global.camera.Follow(&player->center_pos);
}

void EntityManager::Update()
{
	for (int i = 0; i < Entities.size(); ++i)
	{
		Entities[i]->Update();
	}
	Global.camera.Update();
}

void EntityManager::Draw()
{
	for (int i = 0; i < Entities.size(); ++i)
	{
		Entities[i]->Draw();
	}
}
