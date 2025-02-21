#include "AnimationManager.h"

AnimationManager::AnimationManager()
{}

AnimationManager::AnimationManager(Animation Animation)
{
	animation = Animation;
	loop = false;
	flip = SDL_FLIP_NONE;
}

void AnimationManager::Play(Animation _animation)
{
	if (animation.texture.getTex() == _animation.texture.getTex())
		return;
	animation = _animation;
	animation.CurrentFrame = 0;
	timer = 0;
	loop = animation.loop;
}

void AnimationManager::Update()
{
	timer += Global.DeltaTime;

	if (timer <= animation.FrameSpeed)
		return;

	timer = 0;
	animation.CurrentFrame += 1;

	if (animation.CurrentFrame >= animation.FrameCount) {
		animation.CurrentFrame = 0;
		loop = false;
	}
}

bool AnimationManager::IsFlip()
{
	if (flip != SDL_FLIP_NONE)
		return true;
	return false;
}

bool AnimationManager::FrameEnd()
{
	return animation.CurrentFrame + 1 >= animation.FrameCount;
}

Rect AnimationManager::getRect()
{
	return Rect(animation.CurrentFrame * animation.FrameWidth, 0, animation.FrameWidth, animation.FrameHeight);
}
