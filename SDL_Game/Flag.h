#pragma once
#include "Entity.h"
#include "Player.h"

class Flag : public Entity
{
private:
	Player* player;
public:
	Flag();
	Flag(Vector pos, Player* player);
	~Flag()
	{
		//delete player;
		freeEntities();
		freeAnimations();
		LOG("Flag destroyed");
	}
	void Update(const float& dt);
	void Draw();
	void OnCollideWithPlayer();
};

