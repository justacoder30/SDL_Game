#pragma once
#include "Enemy.h"

class Enemy;

class IEnemyState
{
public:
	virtual IEnemyState* Update(Enemy& enemy) = 0;
};

class IdleEnemyState : public IEnemyState {
public:
	IEnemyState* Update(Enemy& enemy) override;
};

class RunEnemyState : public IEnemyState {
public:
	IEnemyState* Update(Enemy& enemy) override;
};