#pragma once
#include <SDL2/SDL.h>
#include "Camera.h"
#include "Font.h"

class GLOBAL
{
private:
	Uint64 startTime;
public:
	SDL_Renderer* Renderer;
	Camera camera;
	Font font;
	float scale;
	double DeltaTime;
	bool gameWin;
	bool gameLose;
	float Score = 0;
	bool gameLoop = true;

	void Update();
	void fpsShow();
};

extern GLOBAL Global;

