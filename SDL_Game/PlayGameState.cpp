#include "PlayGameState.h"

PlayGameState::PlayGameState(Game* game) :IGameState(game)
{
	entityManager = new EntityManager(game->getLevel());/*
	std::thread t = std::thread(&EntityManager::watForInit, entityManager);
	t.join();*/
	//entityManager->watForInit();

	add(entityManager);
}

void PlayGameState::Update(const float& dt)
{
	if (Key[SDL_SCANCODE_ESCAPE]) {
		game->SaveState();
		game->ChangeState(std::make_shared<PauseState>(game));
	}

	if (entityManager->LoseGame()) {
		game->ChangeState(std::make_shared<LoseGameState>(game));
	}

	if (entityManager->isChangLevel()) {
		game->ChangeState(std::make_shared<WinGameState>(game));
	}
	Entity::Update(dt);
}
