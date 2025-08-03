#include "Texture.h"
#include <SDL2/SDL_image.h>
#include<iostream>

Texture::Texture()
{}

Texture::Texture(const std::string& f_path)
{

	texture = IMG_LoadTexture(Global.Renderer, f_path.c_str());
	if (texture == NULL) {
		printf("Unable to create texture from %s! SDL Error: %s\n", f_path.c_str(), SDL_GetError());
		return;
	}
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SetScaleMode(SDL_ScaleModeNearest);
	path = f_path;
	//SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	//SetScaleMode(SDL_SCALEMODE_LINEAR);
}

float Texture::getWidth() const
{
	return w;
}

float Texture::getHeight() const
{
	return h;
}

SDL_Rect Texture::getRect() const
{
	SDL_Rect rect = {
		0,
		0,
		w,
		h,
	};
	return rect;
}

SDL_FRect Texture::getFRect() const
{
	SDL_FRect rect = {
		0,
		0,
		float(w),
		float(h),
	};
	return rect;
}

SDL_Texture* Texture::getTex() const
{
	return texture;
}

void Texture::Free()
{
	SDL_DestroyTexture(texture);
	texture = NULL;
}

Texture Texture::CreateTextTTF(const std::string& text)
{
	SDL_Surface* surface = TTF_RenderText_Solid(Global.font.GetFont(), text.c_str(), {255, 255, 255});
	texture = SDL_CreateTextureFromSurface(Global.Renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	SDL_SetTextureScaleMode(texture, SDL_ScaleModeNearest);
	return *this;
}

Texture Texture::SetScaleMode(const SDL_ScaleMode& scaleMode)
{
	SDL_SetTextureScaleMode(texture, scaleMode);
	return *this;
}

Texture Texture::SetColor(const Uint8& r, const Uint8& g, const Uint8& b)
{
	//SDL_SetTextureColorMod(texture, r, g, b);
	color = { r, g, b, 255};
	return *this;
}
