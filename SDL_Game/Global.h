#pragma once
#include <SDL2/SDL.h>
#include "Camera.h"
#include "Font.h"
#include "ThreadPool.h"

#define LOG(x) std::cout << x << std::endl

class GLOBAL
{
private:
	Uint64 startTime = SDL_GetPerformanceCounter();
	Uint64 lastTime = startTime;
public:
	SDL_Renderer* Renderer;
	Camera camera;
	float freezeFrame = 0.0f;
	Font font;
	float scale;
	float DeltaTime = 0;
	//double DeltaTime;
	bool gameWin;
	bool gameLose;
	float Score = 0;
	bool gameLoop = true;
	ThreadPool pool;

	void Update();
	void fpsShow();
};

extern GLOBAL Global;

