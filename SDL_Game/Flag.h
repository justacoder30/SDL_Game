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
	void Update();
	void Draw();
	void OnCollideWithPlayer();
};

