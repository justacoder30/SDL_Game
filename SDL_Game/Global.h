#pragma once
#include <SDL3/SDL.h>
#include "Camera.h"

class GLOBAL
{
private:
	Uint64 startTime;
public:
	SDL_Renderer* Renderer;
	Camera camera;
	float scale;
	double DeltaTime;
	bool gameLoop = true;

	void Update();
	void fpsShow();
};

extern GLOBAL Global;

