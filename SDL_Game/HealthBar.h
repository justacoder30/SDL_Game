#pragma once
#include "Entity.h"
class HealthBar : public Entity
{
private:
	Entity* entity;
	SDL_Color color;
	float time = 0;
	float durationTime;
	bool erase = false;
	bool staticDraw = false;
	float og_x;
	void DrawTransform();
	void DrawStatic();
public:
	HealthBar();
	HealthBar(Entity *entity, Vector pos, Vector size);
	HealthBar SetColor(Uint8 r, Uint8 g, Uint8 b);
	HealthBar SetStatic();
	void Update();
	void UpdateLength();
	void Draw();
	HealthBar SetErase();
};

