#pragma once
#include "Entity.h"
#include "Player.h"
class Heart : public Entity
{
private:
	Player* player;
public:
	Heart();
	Heart(Vector pos, Player* player);
	void Update();
	void Draw();
	void OnCollideWithPlayer();
};

