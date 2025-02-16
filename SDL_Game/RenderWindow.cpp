#include "RenderWindow.h"
#include <iostream>

RenderWindow window;

RenderWindow::RenderWindow()
{}

RenderWindow::RenderWindow(const char* tittle, int SCREEN_WIDTH, int SCREEN_HEIGHT, SDL_WindowFlags flags)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		printf("Failed to initialize!\n");
	}

	//Create window
	window = SDL_CreateWindow(tittle, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		printf("Failed to initialize!\n");
	}

	renderer = SDL_CreateRenderer(window, NULL);
	Global.Renderer = renderer;

	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}
	
	float scale = CaculateScale(SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_SetRenderScale(renderer, scale, scale);
	SetViewPort(Global.camera.rect);
}

void RenderWindow::SetViewPort(Rect view)
{
	SDL_Rect Viewport = view.getRect();
	SDL_SetRenderViewport(renderer, &Viewport);
}

void RenderWindow::blit(Texture texture, Rect dest, Rect area)
{
	SDL_FRect src, dst;

	dst = dest.getFRect();
	src = area.getFRect();

	SDL_RenderTextureRotated(renderer, texture.getTex(), &src, &dst, 0.0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::blit(Texture texture, Vector vector, Rect area)
{
	SDL_FRect src = area.getFRect();

	SDL_FRect dst = {
		vector.x,
		vector.y,
		texture.getWidth(),
		texture.getHeight()
	};

	SDL_RenderTextureRotated(renderer, texture.getTex(), &src, &dst, 0.0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::blit(Texture texture, Vector vector, Rect area, SDL_FlipMode flip)
{
	//printf("True");
	SDL_FRect src = area.getFRect();

	SDL_FRect dst = {
		vector.x,
		vector.y,
		src.w,
		src.h
	};

	SDL_RenderTextureRotated(renderer, texture.getTex(), &src, &dst, 0.0, NULL, flip);
}

void RenderWindow::blit(Texture texture, Vector vector, Rect area, float scale)
{
	//printf("True");
	SDL_FRect src = area.getFRect();

	SDL_FRect dst = {
		vector.x,
		vector.y,
		src.w * scale,
		src.h * scale
	};

	SDL_RenderTextureRotated(renderer, texture.getTex(), &src, &dst, 0.0, NULL, SDL_FLIP_NONE);
}

float RenderWindow::CaculateScale(float w, float h)
{
	float scale_x = w / Global.camera.rect.w;
	float scale_y = h / Global.camera.rect.h;

	//std::cout << w << Global.camera.rect.w;;

	return std::min(scale_x, scale_y);
}

void RenderWindow::SetFullScreen(SDL_WindowFlags flags)
{
	SDL_SetWindowFullscreen(window, flags);
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
	//Update screen
	//SDL_SetRenderScale(renderer, 4, 4);

	SDL_RenderPresent(renderer);

}

void RenderWindow::quit()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
