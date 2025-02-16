#include "Texture.h"
#include <SDL3_image/SDL_image.h>
#include<iostream>

Texture::Texture()
{}

Texture::Texture(std::string f_path)
{

	texure = IMG_LoadTexture(Global.Renderer, f_path.c_str());
	if (texure == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s\n", f_path.c_str(), SDL_GetError());
		return;
	}

	SetScaleMode(SDL_SCALEMODE_NEAREST);
}

float Texture::getWidth()
{
	return texure->w;
}

float Texture::getHeight()
{
	return texure->h;
}

SDL_Rect Texture::getRect()
{
	SDL_Rect rect = {
		0,
		0,
		texure->w,
		texure->h,
	};
	return rect;
}

SDL_FRect Texture::getFRect()
{
	SDL_FRect rect = {
		0,
		0,
		float(texure->w),
		float(texure->h),
	};
	return rect;
}

SDL_Texture* Texture::getTex()
{
	return texure;
}

void Texture::SetScaleMode(SDL_ScaleMode scaleMode) 
{
	SDL_SetTextureScaleMode(texure, scaleMode);
}

void Texture::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(texure, r, g, b);
}
