#pragma once
#include <SDL2/SDL.h>
#include "Vector.h"
#include "Global.h"
#include "EntityManager.h"
#include "Input.h"
#include "IGameState.h"

const int SCREEN_WIDTH = 1920;
//const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1080;
//const int SCREEN_HEIGHT = 720;

class IGameState;


class Game
{
private:
	EntityManager *entityManager;
	IGameState *currentState;
	IGameState *preveriousState;
	IGameState *nextState;
	int currentLevelIndex = 1;
	std::vector<std::string> levels;

public:
	Game();
	
	void ChangeState(IGameState* newState);
	void ChangeToPreState();
	void ChangeToNextLevel();
	void ResetLevel();
	void SaveState();
	IGameState *getPreState();
	IGameState *getCurrentState();
	std::string getLevel();
	void Update();
	void Draw();
	void Run();
};

