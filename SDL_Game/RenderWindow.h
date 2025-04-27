#pragma once
#include <SDL3/SDL.h>
#include "Texture.h"
#include "Rect.h"
#include "Vector.h"

class RenderWindow
{
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	float CaculateScale(float w, float h);
	bool fullscreen;
	
public:
	RenderWindow();
	RenderWindow(const char* tittle, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool _fullscreen);
	void SetViewPort(Rect view);
	Vector GetWindowSize();
	void blit(Texture texture, Rect dest, Rect area, float rotate = 0.0, SDL_FlipMode flip = SDL_FLIP_NONE);
	void blit(Texture texture, Vector vector, Rect area);
	void blit(Texture texture, Vector vector, Rect area, SDL_FlipMode flip);
	void blit(Texture texture, Vector vector, Rect area, float scale);
	void DrawRect(Rect rect);
	void SetFullScreen(SDL_WindowFlags flags);
	void FullScreenToggle();
	void SetColor(Uint8 r, Uint8 g, Uint8 b);
	void Clear();
	void Render();
	void quit();
};

extern RenderWindow window;

