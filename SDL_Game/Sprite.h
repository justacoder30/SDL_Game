#pragma once
#include "Entity.h"

class Sprite: public Entity
{
public:
	Sprite();
	Sprite(std::string dir, Vector pos, Vector size);
	Sprite(std::string dir);
	void Update();
	void Draw();

};

