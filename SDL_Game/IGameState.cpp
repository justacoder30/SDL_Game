#include "IGameState.h"

IGameState::IGameState(Game* game)
{
	this->game = game;
}

void MenuState::Update()
{
	if (Key[SDL_SCANCODE_J]) {
		game->ChangeState(new PlayGameState(game));
	}
	if (Key[SDL_SCANCODE_K]) {
		game->ChangeToPreState();
	}
	Entity::Update();
}

void MenuState::Draw()
{
	Entity::Draw();
}

void PlayGameState::Update()
{
	if (Key[SDL_SCANCODE_ESCAPE]) {
		game->SaveState();
		game->ChangeState(new MenuState(game));
	}
	Entity::Update();
}

void PlayGameState::Draw()
{
	Entity::Draw();
}
