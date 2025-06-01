#pragma once
#include <SDL3/SDL.h>
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
extern const bool* Key;
extern bool PreKey[SDL_SCANCODE_COUNT];
