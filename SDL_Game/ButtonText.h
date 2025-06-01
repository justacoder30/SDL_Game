#pragma once
#include "Entity.h"
#include "Input.h"

class ButtonText: public Entity
{
private:
	Texture tex;
	Vector size;
	SDL_Color baseColor;
	SDL_Color hoveringColor;
	SDL_Color currentColor;
	Vector pos;
	bool isClicked;
public:
	ButtonText();
	ButtonText(std::string text, Vector pos, Vector size);
	ButtonText *SetColor(Uint8 r, Uint8 g, Uint8 b);
	ButtonText *SetColorHovering(Uint8 r, Uint8 g, Uint8 b);
	void Update();
	void Draw();
	bool Clicked();
};

