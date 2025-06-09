#include "RenderWindow.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>

RenderWindow window;

RenderWindow::RenderWindow()
{}

RenderWindow::RenderWindow(const char* tittle, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool _fullscreen) :fullscreen(_fullscreen)
{
	if (!TTF_Init())
	{
		SDL_Log("SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError());
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		printf("Failed to initialize!\n");
	}

	//Create window
	window = SDL_CreateWindow(tittle, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_SetWindowFullscreen(window, fullscreen);
	
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		printf("Failed to initialize!\n");
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	Global.Renderer = renderer;

	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}
	
	Global.scale = CaculateScale(GetWindowSize().x, GetWindowSize().y);
	Global.camera.SetCamera(GetWindowSize());
	//SDL_SetRenderVSync(renderer, 1);
	//SDL_SetWindowSurfaceVSync(window, 1);
	
}

void RenderWindow::SetViewPort(Rect view)
{
	SDL_Rect Viewport = view.getRect();
	SDL_RenderSetViewport(renderer, &Viewport);
}

Vector RenderWindow::GetWindowSize()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return Vector(w, h);
}

void RenderWindow::blit(Texture texture, Rect dest, Rect area, float rotate, SDL_RendererFlip  flip)
{
	SDL_Rect src, dst;

	dst = dest.getRect();
	src = area.getRect();

	SDL_RenderCopyEx(renderer, texture.getTex(), &src, &dst, rotate, NULL, flip);
}

void RenderWindow::blit(Texture texture, Vector pos, Rect area, float scale, SDL_RendererFlip  flip)
{
	SDL_Rect src = area.getRect();

	SDL_Rect dst = {
		pos.x,
		pos.y,
		src.w * scale,
		src.h * scale
	};

	SDL_RenderCopyEx(renderer, texture.getTex(), &src, &dst, 0.0, NULL, flip);
}

void RenderWindow::blit(Texture texture, Vector pos, Rect area, Vector size)
{
	SDL_Rect src = area.getRect();

	SDL_Rect dst = {
		pos.x,
		pos.y,
		size.x,
		size.y
	};

	SDL_RenderCopyEx(renderer, texture.getTex(), &src, &dst, 0.0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::blit(Texture texture, Vector pos, Vector size)
{
	SDL_Rect dst = {
		pos.x,
		pos.y,
		size.x,
		size.y
	};

	SDL_RenderCopyEx(renderer, texture.getTex(), NULL, &dst, 0.0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::blit(Texture texture, Vector pos)
{
	SDL_Rect dst = {
		0,
		0,
		texture.getWidth(),
		texture.getHeight()
	};

	SDL_RenderCopyEx(renderer, texture.getTex(), NULL, &dst, 0.0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::DrawRect(Rect rect)
{
	SDL_Rect frect = rect.getRect();
	SDL_RenderDrawRect(renderer, &frect);
}

void RenderWindow::DrawFillRect(Rect rect)
{
	SDL_Rect frect = rect.getRect();
	SDL_RenderFillRect(renderer, &frect);
}

float RenderWindow::CaculateScale(float w, float h)
{
	float scale_x = w / Global.camera.rect.w;
	float scale_y = h / Global.camera.rect.h;

	return std::min(scale_x, scale_y);
}

void RenderWindow::SetFullScreen(SDL_WindowFlags flags)
{
	SDL_SetWindowFullscreen(window, flags);
}

void RenderWindow::FullScreenToggle()
{
	fullscreen = !fullscreen;
	SDL_SetWindowFullscreen(window, fullscreen);
	Global.scale = CaculateScale(GetWindowSize().x, GetWindowSize().y);
	Global.camera.SetCamera(GetWindowSize());
}

void RenderWindow::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
}

void RenderWindow::Clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::Render()
{
	SDL_RenderSetScale(renderer, Global.scale, Global.scale);
	SetViewPort(Global.camera.rect);
	SDL_RenderPresent(renderer);
}

void RenderWindow::quit()
{
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	SDL_Quit();
}
