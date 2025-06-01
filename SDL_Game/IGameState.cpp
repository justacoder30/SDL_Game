#include "IGameState.h"

IGameState::IGameState(Game* game)
{
	this->game = game;
}

void MenuState::Update()
{
	if (playBtn->Clicked()) {
		game->ChangeState(new PlayGameState(game));
	}
	if (exitBtn->Clicked()) {
		Global.gameLoop = false;
	}
	Entity::Update();
}

PlayGameState::PlayGameState(Game* game) :IGameState(game)
{
	entityManager = new EntityManager(game->getLevel());
	add(entityManager);
}

void PlayGameState::Update()
{
	if (Key[SDL_SCANCODE_ESCAPE]) {
		game->SaveState();
		game->ChangeState(new PauseState(game));
	}
	if (entityManager->isChangLevel()) {
		game->ChangeToNextLevel();
		game->ChangeState(new PlayGameState(game));
	}
	Entity::Update();
}

void PauseState::Update()
{
	if (countinueBtn->Clicked()) {
		game->ChangeToPreState();
	}
	if (newGameBtn->Clicked()) {
		game->ResetLevel();
		game->ChangeState(new PlayGameState(game));
	}
	if (exitBtn->Clicked()) {
		Global.gameLoop = false;
	}
	Entity::Update();
}
