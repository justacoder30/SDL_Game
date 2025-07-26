#pragma once
#include <SDL2/SDL.h>
#include "Vector.h"
class Rect
{
private:
	void setRect();
public:
	Rect();
	Rect(const float& _x, const float& _y, const float& _w, const float& _h);
	Rect(const Vector& pos, const Vector& size);
	Vector pos, size;
	float x, y, w, h;
	float top, bottom, left, right = 0;
	bool checkCollide(const Rect& rect);
	SDL_FRect getFRect();
	SDL_Rect getRect();
	void printf();
};

