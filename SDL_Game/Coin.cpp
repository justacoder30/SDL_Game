#include "Coin.h"

Coin::Coin(int level, Vector pos, Player player)
{
	animations = {
		{ Idle, Animation("resource/img/Item/Coin.png", 5, 0.08) },
	};

	current = Idle;
}

void Coin::Update()
{
	UpdateAnimation();
}

void Coin::OnCollideWithPlayer()
{

}
