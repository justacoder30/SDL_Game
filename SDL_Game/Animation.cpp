#include "Animation.h"

Animation::Animation()
{}

Animation::Animation(const char* f_p, int frame_count, float frame_speed, bool Loop)
{
	texture = Texture(f_p);
	FrameCount = frame_count;
	FrameSpeed = frame_speed;
	loop = Loop;
	CurrentFrame = 0;
	FrameWidth = texture.getWidth() / FrameCount;
	FrameHeight = texture.getHeight();
}

int Animation::LastFrame()
{
	return FrameCount-1;
}
