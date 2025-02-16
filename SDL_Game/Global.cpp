#include "Global.h"
#include <iostream>

GLOBAL Global = GLOBAL();

void GLOBAL::Update() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			gameLoop = false;
	}

	DeltaTime = (SDL_GetTicks() - startTime) / 1000.0;
	startTime = SDL_GetTicks();
}

void GLOBAL::fpsShow()
{
	std::cout << (1.0 / Global.DeltaTime) << std::endl;
}
