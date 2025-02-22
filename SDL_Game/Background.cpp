#include "Background.h"

Background::Background()
{
	tex = Texture("resource/img/Background/Background1.png");
	rect = Rect(0, 0, tex.getWidth(), tex.getHeight());
}

void Background::Update()
{
	return;
}

void Background::Draw()
{
	float scale = Global.camera.rect.w / tex.getWidth();
	window.blit(tex, GetPos(), rect, scale);
}
