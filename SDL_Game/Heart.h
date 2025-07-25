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
	void Update(const float& dt);
	void Draw();
	void OnCollideWithPlayer();
};

