#pragma once
#include <SDL3/SDL.h>
#include "Camera.h"

class GLOBAL
{
private:
	Uint64 startTime;
	SDL_Event event;
public:
	SDL_Renderer* Renderer;
	Camera camera;
	double DeltaTime;
	bool gameLoop = true;

	void Update();
};

extern GLOBAL Global;
