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

	currentState = std::make_shared<MenuState>(this);
    State = std::make_shared<MenuState>(this).get();
	//preveriousState = std::move(currentState);
	//delete currentState;
}

void Game::ChangeState(std::shared_ptr<IGameState> newState)
{  
    if (nextState == newState) return;  
	//nextState = std::move(newState);
	nextState = newState;
	newState = nullptr;
}  

void Game::ChangeToPreState()  
{  
    if (nextState == preveriousState) return;  
	//nextState = std::move(preveriousState);
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
	//preveriousState = std::move(currentState);
	preveriousState = currentState;
}

std::shared_ptr<IGameState> Game::getPreState()
{
	//return std::move(preveriousState);
	return preveriousState;
}

std::shared_ptr<IGameState> Game::getCurrentState()
{
	//return std::move(currentState);
	return currentState;
}

std::string Game::getLevel()
{
	return levels[currentLevelIndex];
}

void Game::Update()
{
	
	float dt = Global.DeltaTime;
	
	currentState->Update(dt);

	if (nextState != nullptr) {
		//currentState = std::move(nextState);
		currentState = nextState;
		nextState = nullptr;
	}
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
		Input.Update();
		Global.Update();
		if(Global.freezeFrame > 0.0f) {
			Global.freezeFrame -= Global.DeltaTime;
			continue;
			//if (Global.freezeFrame < 0.0f) Global.freezeFrame = 0.0f;
		}
		Update();
		Draw();
	}
}