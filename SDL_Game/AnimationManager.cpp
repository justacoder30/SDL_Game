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
		if (animation.loop) animation.CurrentFrame = 0;
		else animation.CurrentFrame = animation.LastFrame();
	}
}

bool AnimationManager::IsFlip()
{
	if (flip != SDL_FLIP_NONE)
		return true;
	return false;
}

bool AnimationManager::IsDone()
{
	if (animation.CurrentFrame == animation.LastFrame() && timer + Global.DeltaTime > animation.FrameSpeed) {
		return true;
	}

	return false;
}

Rect AnimationManager::getRect()
{
	return Rect(animation.CurrentFrame * animation.FrameWidth, 0, animation.FrameWidth, animation.FrameHeight);
}
