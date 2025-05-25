#include "Rect.h"
#include <iostream>


Rect::Rect()
{}

Rect::Rect(float _x, float _y, float _w, float _h) : x(_x), y(_y), w(_w), h(_h)
{
	top = y;
	bottom = y + h;
	left = x;
	right = x + w;
}

bool Rect::checkCollide(Rect rect)
{
	return (top < rect.bottom and
		bottom > rect.top and
		left < rect.right and
		right > rect.left);
}

SDL_FRect Rect::getFRect()
{
	SDL_FRect frect;
	frect.x = x;
	frect.y = y;
	frect.w = w;
	frect.h = h;
	return frect;
}

SDL_Rect Rect::getRect()
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return rect;
}

void Rect::printf()
{
	std::cout << "(" << x << ", " << y << ", " << w << ", " << h << ")" << std::endl;
}
