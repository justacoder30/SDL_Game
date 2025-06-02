#include "Heart.h"

Heart::Heart(Vector pos, Player* player)
{
	animations = {
		{ Idle, Animation("resource/img/Item/Big Heart Idle (18x14).png", 8, 0.08) },
	};

	current = Idle;
	score = 35;
	this->player = player;

	size = Vector(animations[Idle].FrameWidth, animations[Idle].FrameHeight);

	rect = Rect(pos, size);
	hp = 10;
}

void Heart::Update()
{
	UpdateAnimation();
	OnCollideWithPlayer();
}

void Heart::Draw()
{
	DrawAnimateGroup();
}

void Heart::OnCollideWithPlayer()
{
	if (rect.checkCollide(player->rect)) {
		player->currentHp += hp;
		if (player->currentHp > player->hp) player->currentHp = player->hp;
		Global.Score += score;
		removeFromTree();
	}
}
