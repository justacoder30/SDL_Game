#include "ButtonText.h"

ButtonText::ButtonText()
{
}

ButtonText::ButtonText(std::string text, Vector pos, Vector size)
{
	tex.CreateTextTTF(text);
	this->pos = pos;
	this->size = size;

	rect = Rect(pos, size);
	backDrop = true;
}

ButtonText ButtonText::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	baseColor = { r, g, b };
	hoveringColor = { r, g, b };
	tex.SetColor(baseColor.r, baseColor.g, baseColor.b);
	return *this;
}

ButtonText ButtonText::SetColorHovering(Uint8 r, Uint8 g, Uint8 b)
{
	hoveringColor = { r, g, b };
	return *this;
}

void ButtonText::Update()
{
	Rect newrect = Rect((pos + Global.camera.rect.pos) * Global.scale, size * Global.scale);

	if (Input.MouseHovering(newrect)) {
		currentColor = hoveringColor;
		if (Input.MouseOnRelease()) isClicked = true;
	}
	else currentColor = baseColor;

	tex.SetColor(currentColor.r, currentColor.g, currentColor.b);
}

void ButtonText::Draw()
{
	window.blit(tex, pos, size);
}

bool ButtonText::Clicked()
{
	if (!isClicked) return false;
	SoundManager::PlaySoundEffect("button_click");
	return true;
}
