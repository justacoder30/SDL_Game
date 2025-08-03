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
	~Heart() {
		//if (player != nullptr) delete player;
		freeEntities();
		freeAnimations();
		LOG("Heart destroyed");
	}
	void Update(const float& dt);
	void Draw();
	void OnCollideWithPlayer();
};

