#pragma once
#include <SDL2/SDL.h>
#include "Rect.h"

class INPUT
{
private:
	SDL_Event event;
	bool onRelease;
	void CopyKey();
	void setMouse();
public:
	Rect mouseRect;
	INPUT() {}
	void Update();
	bool MouseOnRelease();
	bool MouseHovering(Rect rect);
};

extern INPUT Input;
extern const Uint8* Key;
extern Uint8 PreKey[SDL_NUM_SCANCODES];
