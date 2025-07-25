#include "Coin.h"

Coin::Coin(Vector pos, Player &player)
{
	animations = {
		{ Idle, Animation("resource/img/Item/Coin.png", 5, 0.08) },
	};

	current = Idle;
	score = 15;
	this->player = &player;

	size = Vector(animations[Idle].FrameWidth, animations[Idle].FrameHeight);

	rect = Rect(pos, size);
}

void Coin::Update(const float& dt)
{
	UpdateAnimation(dt);
	OnCollideWithPlayer();
}

void Coin::Draw()
{
	Entity::DrawAnimateGroup();
}

void Coin::OnCollideWithPlayer()
{
	if (player == NULL) return;
	if (rect.checkCollide(player->rect)) {
		Global.Score += score;
		SoundManager::PlaySoundEffect("coin");
		removeFromTree();
	}
}
