#pragma once
#include <SDL3/SDL.h>
#include "Vector.h"

class Rect
{
private:
	void setRect();
public:
	Rect();
	Rect(float _x, float _y, float _w, float _h);
	Rect(Vector pos, Vector size);
	Vector pos, size;
	float x, y, w, h;
	float top, bottom, left, right = 0;
	bool checkCollide(Rect rect);
	SDL_FRect getFRect();
	SDL_Rect getRect();
	void printf();
};

