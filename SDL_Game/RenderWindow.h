#pragma once
#include <SDL2/SDL.h>
#include "Texture.h"
#include "Rect.h"
#include "Vector.h"

class RenderWindow
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	
	bool fullscreen;
	
public:
	RenderWindow();
	RenderWindow(const char* tittle, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool _fullscreen);
	void SetViewPort(Rect view);
	Vector GetWindowSize();
	float CaculateScale(float w, float h);
	void blit(Texture& texture, const Rect& dest, const Rect& area, float rotate = 0.0, SDL_RendererFlip  flip = SDL_FLIP_NONE);
	void blit(Texture& texture, const Vector& pos, const Rect& area, float scale = 1, SDL_RendererFlip  flip = SDL_FLIP_NONE);
	void blit(Texture& texture, const Vector& pos, const Rect& area, const Vector& size);
	void blit(Texture& texture, const Vector& pos, const Vector& size);
	void blit(Texture& texture, const Vector& pos);
	void DrawRect(const Rect& rect);
	void DrawFillRect(const Rect& rect);
	void SetFullScreen(SDL_WindowFlags flags);
	void FullScreenToggle();
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void Clear();
	void Render();
	void quit();
};

extern RenderWindow window;

