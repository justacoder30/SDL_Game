#include "Texture.h"
#include <SDL2/SDL_image.h>
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
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SetScaleMode(SDL_ScaleModeNearest);
	//SetScaleMode(SDL_SCALEMODE_LINEAR);
}

float Texture::getWidth()
{
	return w;
}

float Texture::getHeight()
{
	return h;
}

SDL_Rect Texture::getRect()
{
	SDL_Rect rect = {
		0,
		0,
		w,
		h,
	};
	return rect;
}

SDL_FRect Texture::getFRect()
{
	SDL_FRect rect = {
		0,
		0,
		float(w),
		float(h),
	};
	return rect;
}

SDL_Texture* Texture::getTex()
{
	return texture;
}

Texture Texture::CreateTextTTF(std::string text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(Global.font.GetFont(), text.c_str(), {255, 255, 255});
	texture = SDL_CreateTextureFromSurface(Global.Renderer, surface);
	SDL_FreeSurface(surface);
	SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);
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
