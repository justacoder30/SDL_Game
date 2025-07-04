#pragma once
#include "Game.h"
#include "ButtonText.h"
#include "SoundManager.h"

class Game;

class IGameState: public Entity
{
protected:
	Game* game;public:
	IGameState(Game *game);
};

class MenuState : public IGameState {
private:
	ButtonText tittle;
	ButtonText playBtn;
	ButtonText exitBtn;
	Vector btnSize = Vector(99.00, 54.00);
public:
	MenuState(Game* game): IGameState(game) {
		tittle = ButtonText("The Metal Knight", Vector(112.00, 0), Vector(608.00, 192.00)).SetColor(46, 58, 89);

		playBtn = ButtonText("Play", Vector(352.00, 272.00), btnSize).SetColor(255, 0, 0).SetColorHovering(255, 255, 0);

		exitBtn = ButtonText("Exit", Vector(352.00, 352.00), btnSize).SetColor(255, 0, 0).SetColorHovering(255, 255, 0);


		add(new Background(Vector(Global.camera.rect.w, Global.camera.rect.h)));
		add(&tittle);
		add(&playBtn);
		add(&exitBtn);

	}
	void Update();
};

class PauseState : public IGameState {
private:
	ButtonText countinueBtn;
	ButtonText newGameBtn;
	ButtonText exitBtn;
	Vector btnSize = Vector(99.00, 54.00);
public:
	PauseState(Game* game) : IGameState(game) {
		countinueBtn = ButtonText("Countinue", Vector(304.00, 112.00), Vector(208.00, 64.00)).SetColor(255, 255, 255).SetColorHovering(255, 255, 0);

		newGameBtn = ButtonText("New Game", Vector(304.00, 192.00), Vector(208.00, 64.00)).SetColor(255, 255, 255).SetColorHovering(255, 255, 0);

		exitBtn = ButtonText("Exit", Vector(352.00, 272.00), btnSize).SetColor(255, 255, 255).SetColorHovering(255, 255, 0);


		add(&countinueBtn);
		add(&newGameBtn);
		add(&exitBtn);
		SoundManager::PauseMusic();
	}
	void Update();
};

class PlayGameState : public IGameState {
private:
	EntityManager *entityManager;
public:
	PlayGameState(Game* game);
	void Update();
};

class LoseGameState : public IGameState {
private:
	EntityManager entityManager;
	ButtonText tryAgainBtn;
	ButtonText newGameBtn;
	ButtonText exitBtn;
	Vector btnSize = Vector(99.00, 54.00);
public:
	LoseGameState(Game* game) : IGameState(game) {
		tryAgainBtn = ButtonText("Try Again", Vector(304.00, 192.00), Vector(208.00, 64.00)).SetColor(255, 255, 255).SetColorHovering(255, 255, 0);

		newGameBtn = ButtonText("New Game", Vector(304.00, 272.00), Vector(208.00, 64.00)).SetColor(255, 255, 255).SetColorHovering(255, 255, 0);

		exitBtn = ButtonText("Exit", Vector(352.00, 352), btnSize).SetColor(255, 255, 255).SetColorHovering(255, 255, 0);

		ButtonText text = ButtonText("You Death!", Vector(192.00, 16.00), Vector(416.00, 128.00)).SetColor(255, 0, 0);

		add(&text);
		add(&tryAgainBtn);
		add(&newGameBtn);
		add(&exitBtn);
		SoundManager::StopMusic();
		SoundManager::PlaySoundEffect("LoseGame");

	}
	void Update();
};

class WinGameState : public IGameState {
private:
	EntityManager entityManager;
	ButtonText continueBtn;
	ButtonText exitBtn;
	Vector btnSize = Vector(99.00, 54.00);
public:
	WinGameState(Game* game) : IGameState(game) {
		continueBtn = ButtonText("Continue", Vector(304.00, 272.00), Vector(208.00, 64.00)).SetColor(255, 255, 255).SetColorHovering(255, 255, 0);

		exitBtn = ButtonText("Exit", Vector(352.00, 352), btnSize).SetColor(255, 255, 255).SetColorHovering(255, 255, 0);

		ButtonText text = ButtonText("SCORE: " + std::to_string(int(Global.Score)), Vector(192.00, 16.00), Vector(416.00, 128.00)).SetColor(255, 0, 0);

		add(&text);
		add(&continueBtn);
		add(&exitBtn);
		SoundManager::StopMusic();
		SoundManager::PlaySoundEffect("WinGame");
	}
	void Update();
};