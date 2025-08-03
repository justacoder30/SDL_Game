#pragma once
#include "Entity.h"
#include "Player.h"

class Coin: public Entity
{
private:
	Player* player;
public:
	Coin();
	Coin(Vector pos, Player* player);
	~Coin() {
		//if (player != nullptr) delete player;
		freeEntities();
		freeAnimations();
		LOG("Coin destroyed");
	}
	void Update(const float& dt);
	void Draw();
	void OnCollideWithPlayer();
};

