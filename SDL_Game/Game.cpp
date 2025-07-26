#include "Game.h"
#include "Text.h"
#include <SDL2/SDL_mixer.h>
#include "SoundManager.h"
#include "PlayGameState.h"

Game::Game()
{
	float scale = 0;
	Global.camera = Camera(784, 441);
	window = RenderWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, false);
	Global.font.SetFont("resource/font/FreeSans.ttf", 20);
	SoundManager::init();

	levels = { "map1.tmx", "map2.tmx" };

	currentState = new MenuState(this);
	//currentState = new PlayGameState(this);
	preveriousState = currentState;
}

void Game::ChangeState(IGameState* newState)
{
	if (nextState == newState) return;
	delete nextState;
	nextState = newState;
}

void Game::ChangeToPreState()
{
	if (nextState == preveriousState) return;
	delete nextState;
	nextState = preveriousState;
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
	float dt = Global.DeltaTime;
	if(nextState != nullptr) {
		currentState = nextState;
		nextState = nullptr;
	}

	currentState->Update(dt);
}

void Game::Draw()
{
	window.SetColor(0, 0, 0);
	window.Clear();

	currentState->Draw();
	
	window.Render();
	Global.fpsShow();
	//LOG(Global.DeltaTime);
}

void Game::Run()
{
	while (Global.gameLoop) {
		/*Global.pool.enqueue([this]() {
			Update();
		});
		Global.pool.wait();*/
		Update();
		Draw();
	}
	window.quit();
}
