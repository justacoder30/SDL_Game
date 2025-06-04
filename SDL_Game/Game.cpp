#include "Game.h"
#include "Text.h"

Game::Game()
{
	float scale = 0;
	Global.camera = Camera(784, 441);
	//Global.camera = Camera(800, 450);
	//Global.camera = Camera(816, 459);
	//Global.camera = Camera(768, 432);
	window = RenderWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	Global.font.SetFont("resource/font/FreeSans.ttf", 20);


	levels = { "map1.tmx", "map2.tmx" };

	currentState = new MenuState(this);
	preveriousState = currentState;
}

void Game::ChangeState(IGameState* newState)
{
	currentState = newState;
}

void Game::ChangeToPreState()
{
	currentState = preveriousState;
}

void Game::ChangeToNextLevel()
{
	currentLevelIndex++;
	if (currentLevelIndex >= levels.size()) currentLevelIndex = 0;
}

void Game::ResetLevel()
{
	currentLevelIndex = 0;
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

std::string Game::getLevel()
{
	return levels[currentLevelIndex];
}

void Game::Update()
{
	Input.Update();
	Global.Update();

	currentState->Update();
}

void Game::Draw()
{
	window.SetColor(0, 0, 0);
	window.Clear();

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
