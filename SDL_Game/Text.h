#pragma once
#include "Entity.h"
#include "SDL2/SDL_ttf.h"

//FreeSans.ttf
class Text : public Entity
{
private:
    int width;
    int height;
    SDL_Surface* surface;
    SDL_Color textColor = { 255, 255, 255, 0 };
    static std::string f_path;
    static int f_size;
public:
    //static void SetText(std::string f_path, int f_size);
    //TTF_OpenFont(font_path, 24);
};

