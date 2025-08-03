#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "Global.h"

class Texture
{
private:
	SDL_Texture* texture = NULL;
	std::string path;
	int w, h;
public:
	SDL_Color color = { 255, 255, 255, 255 };
	Texture();
	Texture(const std::string& f_path);
	float getWidth() const;
	float getHeight() const;
	SDL_Rect getRect() const;
	SDL_FRect getFRect() const;
	SDL_Texture* getTex() const;
	void Free();
	std::string getPath() const { return path; }
	Texture CreateTextTTF(const std::string& text);
	Texture SetScaleMode(const SDL_ScaleMode& scaleMode);
	Texture SetColor(const Uint8& r, const Uint8& g, const Uint8& b);
};

