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

	moveSpeed = 15;
}

void Background::Update()
{
	for (int i = 0; i < clouds.size(); i++) {
		clouds[i]->pos.x -= moveSpeed * Global.DeltaTime;
		if (clouds[i]->pos.x <= -size.x) clouds[i]->pos.x = size.x;
	}

	for (int i = 0; i < Entities.size(); ++i)
	{
		Entities[i]->Update();
		if (Entities[i]->isRemoved()) {
			Entities.erase(Entities.begin() + i--);
		}
	}
}

void Background::Draw()
{
	float speed = 0;
	for (int i = 0; i < Entities.size(); ++i)
	{
		if (i == 1 || i == 2) {
			Entities[i]->Draw();
			continue;
		}
		for (int j = 0; j < 3; j++) {
			float og_pos = Entities[i]->pos.x;
			
			Entities[i]->pos.x += j * size.x + Global.camera.transform.x * speed;
			Entities[i]->Draw();
			
			Entities[i]->pos.x = og_pos;
		}
		speed += 0.08 ;
	}
}
