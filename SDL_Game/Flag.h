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
	void Update(const float& dt);
	void Draw();
	void OnCollideWithPlayer();
};

