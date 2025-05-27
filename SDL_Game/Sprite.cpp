#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(std::string dir, Vector pos, Vector size)
{
	tex = Texture(dir);
	Sprite::pos = pos;
	Sprite::size = size;
}

Sprite::Sprite(std::string dir)
{
	tex = Texture(dir);
	size = Vector(
		tex.getWidth(),
		tex.getHeight()
	);
}

void Sprite::Update()
{
	rect = Rect(pos, size);
}

void Sprite::Draw()
{
	window.blit(tex, pos, size);
}
