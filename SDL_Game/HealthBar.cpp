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
	Camera& camera = Global.camera;
	Rect newRect = Rect(
		pos + camera.transformStatic,
		size
	);

	rect = Rect(
		pos.x + camera.transformStatic.x,
		pos.y + camera.transformStatic.y,
		rect.w,
		rect.h
	);

	window.SetColor(color.r, color.g, color.b);
	DrawFillRectStatic(newRect);
	window.SetColor(0, 0, 0);
	DrawRectStatic(rect);
	
}

HealthBar::HealthBar()
{}

HealthBar::HealthBar(Entity* entity, Vector pos, Vector size)
{
	this->entity = entity;
	this->pos = pos;
	this->size = size;

	og_x = size.x;
	rect = Rect(pos, size);
	backDrop = true;
	durationTime = 5;
	parent = nullptr;
}

HealthBar::~HealthBar()
{
	parent = nullptr;
	delete parent;
	LOG("HealthBar destroyed");
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

void HealthBar::resetTime()
{
	timer = 0;
}

void HealthBar::Update(const float& dt)
{
	
	UpdateLength();
	if (!erase) return;
	if (timer < durationTime) timer += dt;
	if (timer >= durationTime) {
		timer = 0;
		removeFromTree();
	}
	/*if(entity == nullptr) {
		erase = false;
		return;
	}*/
	Entity::Update(dt);
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
