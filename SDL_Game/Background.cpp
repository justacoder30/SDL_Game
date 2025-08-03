#include "Background.h"

Background::Background(Vector size)
{
	backDrop = true;
	Background::size = size;

	clouds = {
		new Sprite(
			"resource/img/Background/2.png",
			Vector(0, 0),
			Vector(size.x, size.y)
		),
		new Sprite(
			"resource/img/Background/2.png",
			Vector(size.x, 0),
			Vector(size.x, size.y)
		)
	};


	Entities = {
		new Sprite(
			"resource/img/Background/1.png",
			Vector(0, 0),
			Vector(size.x, size.y)
		),
		clouds[0],
		clouds[1],
		new Sprite(
			"resource/img/Background/3.png",
			Vector(0, 0),
			Vector(size.x, size.y)
		),
		new Sprite(
			"resource/img/Background/4.png",
			Vector(0, 0),
			Vector(size.x, size.y)
		),

	};

	moveSpeed = 14;
}

void Background::Update(const float& dt)
{
	for (int i = 0; i < clouds.size(); i++) {
		clouds[i]->pos.x -= moveSpeed * dt;
		if (clouds[i]->pos.x <= -size.x) clouds[i]->pos.x = size.x;
	}

	Entity::Update(dt);
}

void Background::Draw()
{
	//Camera& camera = Global.camera;
	Camera& camera = Camera::Get();
	Vector og_pos;
	float speed = 0;
	
	for (int i = 0; i < Entities.size(); ++i)
	{
		if (i == 1 || i == 2) {
			og_pos = Entities[i]->pos;
			Entities[i]->pos += camera.transformStatic;
			Entities[i]->Draw();
			Entities[i]->pos = og_pos;
			continue;
		}
		for (int j = 0; j < 3; j++) {
			og_pos = Entities[i]->pos;
			Entities[i]->pos += camera.transformStatic;
			Entities[i]->pos.x += j * size.x + camera.transform.x * speed;
			Entities[i]->Draw();
			
			Entities[i]->pos = og_pos;
		}
		speed += 0.05;
	}
}
