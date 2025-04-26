#include "EntityManager.h"

EntityManager::EntityManager(int level)
{
	Entities.push_back(new Background());
	Map map(1, Entities);
	player = new Player(0, Map::GetPos("PlayerPosition"));
	Entities.push_back(player);

	Global.camera.FollowEnity(&player->center_pos);
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
