#pragma once
#include "IGameState.h"

class PlayGameState : public IGameState {
private:
	EntityManager *entityManager;
public:
	PlayGameState(Game* game);
	void Update(const float& dt);
};
