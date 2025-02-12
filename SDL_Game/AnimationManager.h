#pragma once
#include "Animation.h"
#include "Global.h"

class AnimationManager
{
private:
	float timer = 0;
	int step = 0;
public:
	Animation animation;
	bool loop;
	SDL_FlipMode flip;

	AnimationManager();
	AnimationManager(Animation Animation);
	void Play(Animation _animation);
	void Update();
	Rect getRect();
};

