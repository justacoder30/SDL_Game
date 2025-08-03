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
	/*IGameState* currentState;
	IGameState* preveriousState;
	IGameState* nextState;*/
	std::shared_ptr<IGameState> currentState;
	std::shared_ptr<IGameState> preveriousState;
	std::shared_ptr<IGameState> nextState;

	IGameState* State;

	/*std::unique_ptr<IGameState> currentState;
	std::unique_ptr<IGameState> preveriousState;
	std::unique_ptr<IGameState> nextState;*/
	
	int currentLevelIndex = 1;
	std::vector<std::string> levels;

public:
	Game();
	~Game() {
		currentState = nullptr;
		preveriousState = nullptr;
		window.quit();
	}
	void ChangeState(std::shared_ptr<IGameState> newState);
	void ChangeToPreState();
	void ChangeToNextLevel();
	void ResetLevel();
	void SaveState();
	std::shared_ptr<IGameState> getPreState();
	std::shared_ptr<IGameState> getCurrentState();
	std::string getLevel();
	void Update();
	void Draw();
	void Run();
};

