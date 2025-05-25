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

class Attack1State : public IPlayerState {
private:
	bool comboAtk = false;
public:
	IPlayerState* Update(Player& player) override;
};

class Attack2State : public IPlayerState {
private:
	bool comboAtk = false;
public:
	IPlayerState* Update(Player& player) override;
};

class Attack3State : public IPlayerState {
public:
	IPlayerState* Update(Player& player) override;
};

class RunAttackState : public IPlayerState {
public:
	IPlayerState* Update(Player& player) override;
};

class DefendState : public IPlayerState {
public:
	IPlayerState* Update(Player& player) override;
};

class ProtectState : public IPlayerState {
public:
	IPlayerState* Update(Player& player) override;
};


