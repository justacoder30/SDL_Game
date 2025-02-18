#include "RenderWindow.h"
#include <iostream>

RenderWindow window;

RenderWindow::RenderWindow()
{}

RenderWindow::RenderWindow(const char* tittle, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		printf("Failed to initialize!\n");
	}

	//Create window
	window = SDL_CreateWindow(tittle, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	SDL_SetWindowFullscreen(window, fullscreen);
	
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
	
	Global.scale = CaculateScale(GetWindowSize().x, GetWindowSize().y);

	SDL_SetRenderScale(renderer, Global.scale, Global.scale);
	SDL_SetRenderVSync(renderer, 1);
	SDL_SetWindowSurfaceVSync(window, 1);
	SetViewPort(Global.camera.rect);
	
}

void RenderWindow::SetViewPort(Rect view)
{
	SDL_Rect Viewport = view.getRect();
	SDL_SetRenderViewport(renderer, &Viewport);
}

Vector RenderWindow::GetWindowSize()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return Vector(w, h);
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

void RenderWindow::DrawRect(Rect rect)
{
	SDL_FRect frect = rect.getFRect();
	SDL_RenderRect(renderer, &frect);
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
	SDL_SetRenderScale(renderer, Global.scale, Global.scale);
	SetViewPort(Global.camera.rect);

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
