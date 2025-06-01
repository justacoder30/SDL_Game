#include "Flag.h"

Flag::Flag(Vector pos, Player* player)
{
	animations = {
		{ Idle, Animation("resource/img/Flag/flag animation.png", 5, 0.1) },
	};

	current = Idle;

	this->player = player;

	size = Vector(animations[Idle].FrameWidth, animations[Idle].FrameHeight);

	rect = Rect(pos, size);
}

void Flag::Update()
{
	UpdateAnimation();
	OnCollideWithPlayer();
}

void Flag::Draw()
{
	DrawAnimateGroup();
}

void Flag::OnCollideWithPlayer()
{
	if (rect.checkCollide(player->rect)) {
		////removeFromTree();
		//Global.gameLoop = false;
		ChangeLevel();
	}
}

