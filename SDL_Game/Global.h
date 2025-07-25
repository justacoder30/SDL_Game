#pragma once
#include <SDL2/SDL.h>
#include "Camera.h"
#include "Font.h"

#define LOG(x) std::cout << x << std::endl

class GLOBAL
{
private:
	Uint64 startTime;
	Uint64 lastTime;
public:
	SDL_Renderer* Renderer;
	Camera camera;
	Font font;
	float scale;
	float DeltaTime;
	//double DeltaTime;
	bool gameWin;
	bool gameLose;
	float Score = 0;
	bool gameLoop = true;

	void Update();
	void fpsShow();
};

extern GLOBAL Global;

