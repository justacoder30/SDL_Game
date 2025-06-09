#include "Input.h"
#include "Global.h"
#include "RenderWindow.h"

INPUT Input = INPUT();
const Uint8* Key = SDL_GetKeyboardState(NULL);
Uint8 PreKey[SDL_NUM_SCANCODES];

void INPUT::CopyKey()
{
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) { // init them all to false
		PreKey[i] = Key[i];
	}
}

void INPUT::setMouse()
{
	onRelease = false;
	int x, y;
	SDL_GetMouseState(&x, &y);

	mouseRect = Rect(x, y, 1, 1);
}

void INPUT::Update()
{
	CopyKey();

	setMouse();

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			Global.gameLoop = false;
			break;
		case SDL_MOUSEBUTTONUP:
			onRelease = true;
			break;
		}
	}

	if (Key[SDL_SCANCODE_F11] && !PreKey[SDL_SCANCODE_F11])
		window.FullScreenToggle();
}

bool INPUT::MouseOnRelease()
{
	return onRelease;
}

bool INPUT::MouseHovering(Rect rect)
{
	return mouseRect.checkCollide(rect);
}
