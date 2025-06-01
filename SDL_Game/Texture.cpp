#include "Texture.h"
#include <SDL3_image/SDL_image.h>
#include<iostream>

Texture::Texture()
{}

Texture::Texture(std::string f_path)
{

	texture = IMG_LoadTexture(Global.Renderer, f_path.c_str());
	if (texture == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s\n", f_path.c_str(), SDL_GetError());
		return;
	}

	SetScaleMode(SDL_SCALEMODE_NEAREST);
	//SetScaleMode(SDL_SCALEMODE_LINEAR);
}

float Texture::getWidth()
{
	return texture->w;
}

float Texture::getHeight()
{
	return texture->h;
}

SDL_Rect Texture::getRect()
{
	SDL_Rect rect = {
		0,
		0,
		texture->w,
		texture->h,
	};
	return rect;
}

SDL_FRect Texture::getFRect()
{
	SDL_FRect rect = {
		0,
		0,
		float(texture->w),
		float(texture->h),
	};
	return rect;
}

SDL_Texture* Texture::getTex()
{
	return texture;
}

Texture Texture::CreateTextTTF(std::string text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(Global.font.GetFont(), text.c_str(), 0, {255, 255, 255});
	texture = SDL_CreateTextureFromSurface(Global.Renderer, surface);
	SDL_DestroySurface(surface);
	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
	return *this;
}

Texture Texture::SetScaleMode(SDL_ScaleMode scaleMode)
{
	SDL_SetTextureScaleMode(texture, scaleMode);
	return *this;
}

Texture Texture::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(texture, r, g, b);
	return *this;
}
