#include <iostream>
#include "Global.h"

GLOBAL Global = GLOBAL();

void GLOBAL::Update() {
	lastTime = startTime;
	startTime = SDL_GetPerformanceCounter();
	DeltaTime = (float)(startTime - lastTime) / SDL_GetPerformanceFrequency();
	if (DeltaTime > 1/60.f) DeltaTime = 1/60.f;
}

void GLOBAL::fpsShow()
{
	std::cout << int(1.0 / DeltaTime) << std::endl;
}
