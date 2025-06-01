#pragma once
#include "Game.h"
#include "ButtonText.h"

class Game;

class IGameState: public Entity
{
protected:
	Game* game;
public:
	IGameState(Game *game);
	/*virtual void Update() {}
	virtual void Draw() {}*/
};

class MenuState : public IGameState {
private:
	ButtonText* tittle;
	ButtonText* playBtn;
	ButtonText* exitBtn;
	Vector btnSize = Vector(99.00, 54.00);
public:
	MenuState(Game* game): IGameState(game) {
		tittle = new ButtonText("The Metal Knight", Vector(112.00, 0), Vector(608.00, 192.00));
		tittle->SetColor(46, 58, 89);

		playBtn = new ButtonText("Play", Vector(352.00, 272.00), btnSize);
		playBtn->SetColor(255, 0, 0)->SetColorHovering(255, 255, 0);

		exitBtn = new ButtonText("Exit", Vector(352.00, 352.00), btnSize);
		exitBtn->SetColor(255, 0, 0)->SetColorHovering(255, 255, 0);


		add(new Background(Vector(Global.camera.rect.w, Global.camera.rect.h)));
		add(tittle);
		add(playBtn);
		add(exitBtn);

	}
	void Update();
};

class PauseState : public IGameState {
private:
	ButtonText* countinueBtn;
	ButtonText* newGameBtn;
	ButtonText* exitBtn;
	Vector btnSize = Vector(99.00, 54.00);
public:
	PauseState(Game* game) : IGameState(game) {
		countinueBtn = new ButtonText("Countinue", Vector(304.00, 112.00), Vector(208.00, 64.00));
		countinueBtn->SetColor(255, 0, 0)->SetColorHovering(255, 255, 0);

		newGameBtn = new ButtonText("New Game", Vector(304.00, 192.00), Vector(208.00, 64.00));
		newGameBtn->SetColor(255, 0, 0)->SetColorHovering(255, 255, 0);

		exitBtn = new ButtonText("Exit", Vector(352.00, 272.00), btnSize);
		exitBtn->SetColor(255, 0, 0)->SetColorHovering(255, 255, 0);


		add(countinueBtn);
		add(newGameBtn);
		add(exitBtn);

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