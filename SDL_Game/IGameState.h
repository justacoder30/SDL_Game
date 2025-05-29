#pragma once
#include "Game.h"

class Game;

class IGameState: public Entity
{
protected:
	Game* game;
public:
	IGameState(Game *game);
	virtual void Update() {}
	virtual void Draw() {}
};

class MenuState : public IGameState {
public:
	MenuState(Game* game): IGameState(game) {
		add(new Background(Vector(Global.camera.rect.w, Global.camera.rect.h)));
	}
	void Update();
	void Draw();
};

class PlayGameState : public IGameState {
private:
	EntityManager* entityManager;
public:
	PlayGameState(Game* game) : IGameState(game) {
		add(new EntityManager(0));
	}
	void Update();
	void Draw();
};