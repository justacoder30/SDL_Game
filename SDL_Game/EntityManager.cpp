#include "EntityManager.h"

EntityManager::EntityManager(int level)
{
	player = new Player(0);
	//Entities.push_back(new Background());
	Map map(0, Entities);
	Entities.push_back(player);

	Global.camera.FollowEnity(&player->pos);
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
