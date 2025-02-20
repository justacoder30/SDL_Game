#include "Input.h"
#include "Global.h"
#include "RenderWindow.h"

INPUT Input = INPUT();
const bool* Key = SDL_GetKeyboardState(NULL);
bool PrevKey[SDL_SCANCODE_COUNT];

void INPUT::CopyKey()
{
	for (int i = 0; i < SDL_SCANCODE_COUNT; i++) { // init them all to false
		PrevKey[i] = Key[i];
	}
}

void INPUT::Update()
{
	CopyKey();

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_EVENT_QUIT:
			Global.gameLoop = false;
			break;
		}
	}

	if (Key[SDL_SCANCODE_F11] && !PrevKey[SDL_SCANCODE_F11])
		window.FullScreenToggle();
}
