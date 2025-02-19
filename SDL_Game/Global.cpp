#include "Global.h"
#include <iostream>

GLOBAL Global = GLOBAL();

void GLOBAL::Update() {
	

	DeltaTime = (SDL_GetTicks() - startTime) / 1000.0;
	startTime = SDL_GetTicks();
}

void GLOBAL::fpsShow()
{
	std::cout << round(1.0f / Global.DeltaTime) << std::endl;
}
