#pragma once
#include <SDL3/SDL.h>


class INPUT
{
private:
	SDL_Event event;

	void CopyKey();
public:
	INPUT() {}
	void Update();
};

extern INPUT Input;
extern const bool* Key;
extern bool PrevKey[SDL_SCANCODE_COUNT];
