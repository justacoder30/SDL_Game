#include <iostream>
#include "Global.h"

GLOBAL Global = GLOBAL();

void GLOBAL::Update() {
	startTime = SDL_GetPerformanceCounter();
	DeltaTime = (float)(startTime - lastTime) / SDL_GetPerformanceFrequency();
	lastTime = startTime;
}

void GLOBAL::fpsShow()
{
	std::cout << int(1.0 / DeltaTime) << std::endl;
}
