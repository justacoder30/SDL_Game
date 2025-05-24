#pragma once
#include "Player.h"

class Player;

class IPlayerState
{
public:
	virtual IPlayerState* Update(Player& player) = 0;
};

class IdleState : public IPlayerState {
public:
	IPlayerState* Update(Player& player) override;
};

class RunState : public IPlayerState {
public:
	IPlayerState* Update(Player& player) override;
};

class FallState : public IPlayerState {
public:
	IPlayerState* Update(Player& player) override;
};

class JumpState : public IPlayerState {
public:
	IPlayerState* Update(Player& player) override;
};
