#pragma once
#include <SDL3/SDL.h>
#include "Vector.h"
#include "Global.h"
#include "EntityManager.h"
#include "Input.h"

const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;

class Game
{
private:
	EntityManager entityManager;

public:
	Game();
	
	void Update();
	void Draw();
	void Run();
};

