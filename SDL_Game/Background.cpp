#include "Background.h"

Background::Background()
{
	tex = Texture("resource/img/Background/Background1.png");
	pos = Vector(0, 0);
	rect = Rect(0, 0, tex.getWidth(), tex.getHeight());
}

void Background::Update()
{
	return;
}

void Background::Draw()
{
	float scale = Global.camera.rect.w / tex.getWidth();
	window.blit(tex, pos, rect, scale);
}
