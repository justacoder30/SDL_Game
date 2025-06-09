#include "Game.h"
#include "Text.h"
#include <SDL3/SDL_mixer.h>

Mix_Music* gMusic = NULL;

//The sound effects that will be used
Mix_Chunk* gScratch = NULL;
Mix_Chunk* gHigh = NULL;
Mix_Chunk* gMedium = NULL;
Mix_Chunk* gLow = NULL;

Game::Game()
{
	float scale = 0;
	Global.camera = Camera(784, 441);
	window = RenderWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, false);
	Global.font.SetFont("resource/font/FreeSans.ttf", 20);

	SDL_AudioSpec spec;
	spec.freq = 44100;
	spec.format = MIX_DEFAULT_FORMAT;
	spec.channels = 2;
	if (Mix_OpenAudio(0, &spec))
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", SDL_GetError());
	}

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
