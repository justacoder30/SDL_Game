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
	SDL_RendererFlip flip;

	AnimationManager();
	AnimationManager(Animation Animation);
	void Play(Animation _animation);
	void ResetFrame();
	void Update(const float& dt);
	void stop();
	bool IsFlip();
	bool IsDone();
	Rect getRect();
};

