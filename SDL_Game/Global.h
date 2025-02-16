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
	//std::vector<Entity*> Collisions;
	double DeltaTime;
	bool gameLoop = true;

	void Update();
	void fpsShow();
};

extern GLOBAL Global;

