#include "Rect.h"
#include <iostream>


void Rect::setRect()
{
	top = y;
	bottom = y + h;
	left = x;
	right = x + w;
}

Rect::Rect()
{}

Rect::Rect(const float& _x, const float& _y, const float& _w, const float& _h) : x(_x), y(_y), w(_w), h(_h)
{
	this->pos = Vector(x, y);
	this->size = Vector(w, h);
	setRect();
}

Rect::Rect(const Vector& pos, const Vector& size)
{
	this->pos = pos;
	this->size = size;

	x = pos.x;
	y = pos.y;
	w = size.x;
	h = size.y;

	setRect();
}

bool Rect::checkCollide(const Rect& rect)
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
