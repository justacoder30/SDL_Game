#pragma once
#include <SDL3/SDL.h>

class Rect
{
public:
	Rect();
	Rect(float _x, float _y, float _w, float _h);
	float x, y, w, h;
	float top, bottom, left, right;
	bool checkCollide(Rect rect);
	SDL_FRect getFRect();
	SDL_Rect getRect();
	void printf();
};

