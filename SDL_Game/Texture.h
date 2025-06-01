#pragma once
#include <iostream>
#include <SDL3/SDL.h>
#include "Global.h"

class Texture
{
private:
	SDL_Texture* texture;
public:
	Texture();
	Texture(std::string f_path);
	float getWidth();
	float getHeight();
	SDL_Rect getRect();
	SDL_FRect getFRect();
	SDL_Texture* getTex();
	Texture CreateTextTTF(std::string text);
	Texture SetScaleMode(SDL_ScaleMode scaleMode);
	Texture SetColor(Uint8 r, Uint8 g, Uint8 b);
};

