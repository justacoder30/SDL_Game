#include "Game.h"

Game::Game()
{
	Global.camera = Camera(560, 315);	
	window = RenderWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, true);

	entityManager = EntityManager(0);
}

void Game::Update()
{
	Input.Update();
	Global.Update();
	entityManager.Update();
}

void Game::Draw()
{
	window.SetColor(0, 0, 0);
	window.Clear();

	entityManager.Draw();

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
