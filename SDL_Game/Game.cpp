#include "Game.h"



Game::Game()
{
	Global.camera = Camera(800, 450);	
	window = RenderWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, false);

	//currentState = new MenuState(this);
	currentState = new MenuState(this);
	preveriousState = currentState;

	//entityManager = new EntityManager(0);
}

void Game::ChangeState(IGameState* newState)
{
	currentState = newState;
}

void Game::ChangeToPreState()
{
	currentState = preveriousState;
}

void Game::SaveState()
{
	preveriousState = currentState;
}

IGameState* Game::getPreState()
{
	return preveriousState;
}

IGameState* Game::getCurrentState()
{
	return currentState;
}

void Game::Update()
{
	Input.Update();
	Global.Update();

	currentState->Update();
	//entityManager->Update();
}

void Game::Draw()
{
	window.SetColor(0, 0, 0);
	window.Clear();

	//entityManager->Draw();
	currentState->Draw();
	window.Render();
	//Global.fpsShow();
}

void Game::Run()
{
	while (Global.gameLoop) {
		Update();
		Draw();
	}
	window.quit();
}
