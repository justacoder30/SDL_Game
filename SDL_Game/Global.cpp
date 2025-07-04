#include "Global.h"
#include <iostream>

GLOBAL Global = GLOBAL();

void GLOBAL::Update() {
	

	DeltaTime = (SDL_GetTicks64() - startTime) / 1000.0;
	startTime = SDL_GetTicks64();
}

void GLOBAL::fpsShow()
{
	std::cout << round(1.0 / Global.DeltaTime) << std::endl;
}
