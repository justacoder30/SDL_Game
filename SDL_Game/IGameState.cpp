#include "IGameState.h"
#include "PlayGameState.h"

IGameState::IGameState(Game* game)
{
	this->game = game;
}

MenuState::~MenuState()
{
	delete tittle;
	delete playBtn;
	delete exitBtn;
	LOG("MenuState destroyed");
}

void MenuState::Update(const float& dt)
{
	if (playBtn->Clicked()) {
		game->ChangeState(std::make_shared<PlayGameState>(game));
	}
	if (exitBtn->Clicked()) {
		Global.gameLoop = false;
	}

	Entity::Update(dt);
}

//PlayGameState::PlayGameState(Game* game) :IGameState(game)
//{
//	entityManager = new EntityManager(game->getLevel());
//	add(entityManager);
//}
//
//void PlayGameState::Update()
//{
//	if (Key[SDL_SCANCODE_ESCAPE]) {
//		game->SaveState();
//		game->ChangeState(new PauseState(game));
//	}
//
//	if (entityManager->LoseGame()) {
//		game->ChangeState(new LoseGameState(game));
//	}
//
//	if (entityManager->isChangLevel()) {
//		game->ChangeState(new WinGameState(game));
//	}
//	Entity::Update();
//}

void PauseState::Update(const float& dt)
{
	if (countinueBtn->Clicked()) {
		SoundManager::PlayMusic();
		game->ChangeToPreState();
	}
	if (newGameBtn->Clicked()) {
		game->ResetLevel();
		game->ChangeState(std::make_shared<PlayGameState>(game));
		game->getPreState() = nullptr; 
	}
	if (exitBtn->Clicked()) {
		Global.gameLoop = false;
	}
	Entity::Update(dt);
}

void LoseGameState::Update(const float& dt)
{
	if (tryAgainBtn->Clicked()) {
		game->ChangeState(std::make_shared<PlayGameState>(game));
	}
	if (newGameBtn->Clicked()) {
		game->ResetLevel();
		game->ChangeState(std::make_shared<PlayGameState>(game));
	}
	if (exitBtn->Clicked()) {
		Global.gameLoop = false;
	}
	Entity::Update(dt);
}

void WinGameState::Update(const float& dt)
{
	if (continueBtn->Clicked()) {
		game->ChangeToNextLevel();
		game->ChangeState(std::make_shared<PlayGameState>(game));
	}
	if (exitBtn->Clicked()) {
		Global.gameLoop = false;
	}
	Entity::Update(dt);
}
