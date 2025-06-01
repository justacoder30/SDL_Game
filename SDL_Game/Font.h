#pragma once
#include "SDL3_ttf/SDL_ttf.h"
#include <string>

class Font
{
private:
	TTF_Font* font;
public:
	void SetFont(std::string f_path, int f_size) {
		font = TTF_OpenFont(f_path.c_str(), f_size);
		if (font == nullptr)
		{
			SDL_Log("Could not load %s! SDL_ttf Error: %s\n", f_path.c_str(), SDL_GetError());
		}
	}

	TTF_Font* GetFont() {
		return font;
	}
};

