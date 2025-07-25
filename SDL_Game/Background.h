#pragma once
#include "Sprite.h"

class Background : public Entity
{
private:
	std::vector<Entity*> Entities;
	std::vector<Entity*> clouds;
public:
	Background();
	Background(Vector size);
	void Update(const float& dt);
	void Draw();
};

