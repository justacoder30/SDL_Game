#include "Game.h"

Game::Game()
{
	Global.camera = Camera(560, 315);
	window = RenderWindow("SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	entityManager = EntityManager(1);
}

void Game::Update()
{
	
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
