#include <iostream>
#include "Global.h"

GLOBAL Global = GLOBAL();

void GLOBAL::Update() {
	lastTime = startTime;
	startTime = SDL_GetPerformanceCounter();
	DeltaTime = (float)(startTime - lastTime) / SDL_GetPerformanceFrequency();
}

void GLOBAL::fpsShow()
{
	std::cout << int(1.0 / DeltaTime) << std::endl;
}
