#pragma once
#include "Entity.h"
#include "Player.h"

class Coin: public Entity
{
private:
	Player* player;
public:
	Coin();
	Coin(int level, Vector pos, Player player);
	void Update();
	void OnCollideWithPlayer();
};

