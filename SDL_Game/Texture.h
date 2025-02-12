#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Global.h"

class Texture
{
private:
	SDL_Texture* texure;
public:
	Texture();
	Texture(std::string f_path);
	float getWidth();
	float getHeight();
	SDL_Rect getRect();
	SDL_FRect getFRect();
	SDL_Texture* getTex();
	void SetScaleMode(SDL_ScaleMode scaleMode);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
};

