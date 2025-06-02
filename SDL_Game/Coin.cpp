#include "Coin.h"

Coin::Coin(Vector pos, Player *player)
{
	animations = {
		{ Idle, Animation("resource/img/Item/Coin.png", 5, 0.08) },
	};

	current = Idle;
	score = 15;
	this->player = player;

	size = Vector(animations[Idle].FrameWidth, animations[Idle].FrameHeight);

	rect = Rect(pos, size);
}

void Coin::Update()
{
	UpdateAnimation();
	OnCollideWithPlayer();
}

void Coin::Draw()
{
	Entity::DrawAnimateGroup();
}

void Coin::OnCollideWithPlayer()
{
	if (rect.checkCollide(player->rect)) {
		Global.Score += score;
		removeFromTree();
	}
}
