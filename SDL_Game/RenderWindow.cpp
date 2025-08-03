#include "RenderWindow.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

RenderWindow window;

void QuangGameRenderer(
	SDL_Renderer* renderer,
	Texture& texture,
	const Rect* srcrect,
	const Rect* dstrect,
	const float& angle,
	const Vector* center,
	const SDL_RendererFlip flip)
{
	SDL_Vertex verts[4];
	Rect src;
	Vector centerPoint;

	float px[4] = {
		dstrect->x,                // top-left
		dstrect->x + dstrect->w,       // top-right
		dstrect->x + dstrect->w,       // bottom-right
		dstrect->x                 // bottom-left
	};

	float py[4] = {
		dstrect->y,
		dstrect->y,
		dstrect->y + dstrect->h,
		dstrect->y + dstrect->h
	};

	if(!srcrect) src = Rect(0, 0, texture.getWidth(), texture.getHeight());
	else src = *srcrect;

	if (!center) centerPoint = Vector(dstrect->w / 2.0f, dstrect->h / 2.0f);
	else centerPoint = *center;

	if (angle != 0.0f || angle != 360.0f) {
		float cx = dstrect->x + centerPoint.x;
		float cy = dstrect->y + centerPoint.y;
		float angleRad = angle * M_PI / 180.0f;
		float cosA = cosf(angleRad);
		float sinA = sinf(angleRad);

		for (int i = 0; i < 4; ++i) {
			float dx = px[i] - cx;
			float dy = py[i] - cy;
			verts[i].position.x = cosA * dx - sinA * dy + cx;
			verts[i].position.y = sinA * dx + cosA * dy + cy;
		}
	}
	else {
		for (int i = 0; i < 4; ++i) {
			verts[i].position.x = px[i];
			verts[i].position.y = py[i];
		}
	}
	

	float texW = texture.getWidth();
	float texH = texture.getHeight();

	float u0 = src.x / texW;
	float u1 = (src.x + src.w) / texW;
	float v0 = src.y / texH;
	float v1 = (src.y + src.h) / texH;

	float u[4] = { src.x / texW, (src.x + src.w) / texW, (src.x + src.w) / texW, src.x / texW };
	float v[4] = { src.y / texH, src.y / texH, (src.y + src.h) / texH, (src.y + src.h) / texH };

	if (flip & SDL_FLIP_HORIZONTAL) {
		std::swap(u[0], u[1]);
		std::swap(u[3], u[2]);
	}

	if (flip & SDL_FLIP_VERTICAL) {
		std::swap(v[0], v[3]);
		std::swap(v[1], v[2]);
	}

	for (int i = 0; i < 4; ++i) {
		verts[i].tex_coord = { u[i], v[i] };
		verts[i].color = texture.color;
	}

	int indices[6] = { 0, 1, 2, 2, 3, 0 };

	SDL_RenderGeometry(renderer, texture.getTex(), verts, 4, indices, 6);
}

RenderWindow::RenderWindow()
{}

RenderWindow::RenderWindow(const char* tittle, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool _fullscreen) :fullscreen(_fullscreen)
{
	if (TTF_Init() == -1)
	{
		SDL_Log("SDL_ttf could not initialize! SDL_ttf error: %s\n", SDL_GetError());
	}

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		printf("Failed to initialize!\n");
	}

	/*int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", SDL_GetError());
	}*/

	SDL_WindowFlags flags = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_SHOWN;

	//Create window
	window = SDL_CreateWindow(tittle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
	
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		printf("Failed to initialize!\n");
	}

	//renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	Global.Renderer = renderer;

	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
	}
	
	//Global.scale = CaculateScale(GetWindowSize().x, GetWindowSize().y);
	Global.scale = CaculateScale(Global.camera.rect.w, Global.camera.rect.h);
	Global.camera.SetCamera(GetWindowSize());
	/*SDL_SetRenderVSync(renderer, 1);
	SDL_SetWindowSurfaceVSync(window, 1);*/
	
}

void RenderWindow::SetViewPort(Rect view)
{
	SDL_Rect Viewport = {view.x, view.y, view.w + 1, view.h + 2};
	SDL_RenderSetViewport(renderer, &Viewport);
}

Vector RenderWindow::GetWindowSize()
{
	int w, h;
	SDL_GetWindowSize(window, &w, &h);
	return Vector(w, h);
}

void RenderWindow::blit(Texture& texture, const Rect& dest, const Rect& area, float rotate, SDL_RendererFlip  flip)
{
	QuangGameRenderer(renderer, texture, &area, &dest, rotate, NULL, flip);
}

void RenderWindow::blit(Texture& texture, const Vector& pos, const Rect& area, float scale, SDL_RendererFlip  flip)
{
	Rect dst = Rect(pos.x, pos.y, area.w * scale, area.h * scale);
	QuangGameRenderer(renderer, texture, &area, &dst, 0.0, NULL, flip);
}

void RenderWindow::blit(Texture& texture, const Vector& pos, const Rect& area, const Vector& size)
{
	Rect dst = Rect(pos.x, pos.y, size.x, size.x);
	QuangGameRenderer(renderer, texture, &area, &dst, 0.0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::blit(Texture& texture, const Vector& pos, const Vector& size)
{
	Rect dst = Rect(pos.x, pos.y, size.x, size.y);
	QuangGameRenderer(renderer, texture, NULL, &dst, 0.0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::blit(Texture& texture, const Vector& pos)
{
	Rect dst = Rect(pos.x, pos.y, texture.getWidth(), texture.getHeight());
	QuangGameRenderer(renderer, texture, NULL, &dst, 0.0, NULL, SDL_FLIP_NONE);
}

void RenderWindow::DrawRect(const Rect& rect)
{
	SDL_Rect frect = {rect.x, rect.y, rect.w, rect.h};
	SDL_RenderDrawRect(renderer, &frect);
}

void RenderWindow::DrawFillRect(const Rect& rect)
{
	SDL_Rect frect = { rect.x, rect.y, rect.w, rect.h };
	SDL_RenderFillRect(renderer, &frect);
}

float RenderWindow::CaculateScale(float w, float h)
{
	/*float scale_x = w / Global.camera.rect.w;
	float scale_y = h / Global.camera.rect.h;*/

	Vector size = GetWindowSize();
	float scale_x = size.x / w;
	float scale_y = size.y / h;

	return std::min(scale_x, scale_y);
}

void RenderWindow::SetFullScreen(SDL_WindowFlags flags)
{
	SDL_SetWindowFullscreen(window, flags);
}

void RenderWindow::FullScreenToggle()
{
	fullscreen = !fullscreen;
	SDL_WindowFlags flags = fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_SHOWN;
	SDL_SetWindowFullscreen(window, flags);
	Global.scale = CaculateScale(Global.camera.rect.w, Global.camera.rect.h);
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
