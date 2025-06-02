#pragma once
#include "Boss.h"

class Boss;

class IBossState
{
public:
	virtual IBossState* Update(Boss& boss) = 0;
};

class IdleBossState : public IBossState {
public:
	IBossState* Update(Boss& boss);
};

class WalkBossState : public IBossState {
public:
	IBossState* Update(Boss& boss);
};

class HurtBossState : public IBossState {
public:
	IBossState* Update(Boss& boss);
};

class AttackBossState : public IBossState {
public:
	IBossState* Update(Boss& boss);
};

class DeathBossState : public IBossState {
public:
	IBossState* Update(Boss& boss);
};



