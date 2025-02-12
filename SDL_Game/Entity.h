#pragma once
#include "RenderWindow.h"
#include <unordered_map>
#include "Texture.h"
#include "AnimationManager.h"
class Entity
{
private:

public:
	std::unordered_map<std::string, Animation> animations;
	AnimationManager animationManger;
	Texture tex;
	Vector pos;
	Vector velocity;
	Rect rect;
	float speed;
	SDL_FlipMode flip;

	Entity();

	virtual void Update() = 0;
	virtual void Draw() = 0;
};

