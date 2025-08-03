#pragma once
#include "IGameState.h"

class PlayGameState : public IGameState {
private:
	EntityManager *entityManager;
public:
	PlayGameState(Game* game);
	~PlayGameState() {
		delete entityManager;
		LOG("PlayGameState destroyed");
	}
	void Update(const float& dt);
};
