#include "HealthBar.h"

void HealthBar::DrawTransform()
{
	window.SetColor(color.r, color.g, color.b);
	
	Rect newRect = Rect(
		pos + entity->GetPos(),
		size
	);
	DrawFillRectTransform(newRect);
}

void HealthBar::DrawStatic()
{
	Rect newRect = Rect(
		pos,
		size
	);

	window.SetColor(color.r, color.g, color.b);
	DrawFillRectStatic(newRect);
	window.SetColor(0, 0, 0);
	DrawRectStatic(rect);
	
}

HealthBar::HealthBar()
{}

HealthBar::HealthBar(Entity * entity, Vector pos, Vector size)
{
	this->entity = entity;
	this->pos = pos;
	this->size = size;

	og_x = size.x;
	rect = Rect(pos, size);
	backDrop = true;
	durationTime = 50;
}

HealthBar HealthBar::SetColor(Uint8 r, Uint8 g, Uint8 b)
{
	color = { r, g, b };
	return *this;
}

HealthBar HealthBar::SetStatic()
{
	staticDraw = true;
	return *this;
}

void HealthBar::Update()
{
	
	UpdateLength();
	if (!erase) return;
	if (time < durationTime) time += Global.DeltaTime;
	if (time >= durationTime) {
		time = 0;
		removeFromTree();
	}
	Entity::Update();
}

void HealthBar::UpdateLength()
{
	if (entity->currentHp <= 0) entity->currentHp = 0;
	size.x = og_x * entity->currentHp / entity->hp;
}

void HealthBar::Draw()
{
	if (!staticDraw) DrawTransform();
	else {
		DrawStatic();
	}
	Entity::Draw();
}

HealthBar HealthBar::SetErase()
{
	erase = true;
	return *this;
}
