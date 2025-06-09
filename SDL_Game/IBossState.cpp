#include "IBossState.h"

IBossState* IdleBossState::Update(Boss& boss)
{
    boss.current = Idle;
    boss.velocity.x = 0;

    if (boss.isHurt) {
        boss.beingHurt();
        return new HurtBossState();

        /*boss.hurtCnt++;
        if (boss.hurtCnt > 2) {
            boss.beingHurt();
            boss.hurtCnt = 0;
            return new HurtBossState();
        }
        else {
            boss.currentHp -= boss.damageTaken;
            boss.isHurt = false;
        }*/
        
    }

    if (boss.isInEnemyZone()) {
        if (boss.isInAttackZone()) {
            SoundManager::PlaySoundEffect("attack");
            return new AttackBossState();
        }
        if (boss.isEdge() && !boss.checkTurn() || boss.isHitWall() && !boss.checkTurn()) return this;
        return new WalkBossState();
    }

    return this;
}

IBossState* WalkBossState::Update(Boss& boss)
{
    boss.current = Walk;

    if (boss.isInEnemyZone()) {
        boss.velocity.x = boss.center_pos.x < boss.player->center_pos.x ? boss.moveSpeed : -boss.moveSpeed;
        if (boss.isEdge() || boss.isHitWall()) return new IdleBossState;
        if (boss.isInAttackZone()) {
            SoundManager::PlaySoundEffect("attack");
            return new AttackBossState();
        }
    }

    return this;
}

IBossState* HurtBossState::Update(Boss& boss)
{
    boss.current = Hurt;
    boss.isHurt = false;

    boss.velocity.x = boss.moveSpeed / 2 * boss.hurtDirection;
    if (boss.animationManger.IsDone()) {
        if (boss.currentHp <= 0) {
            boss.current = Death;
            return new DeathBossState();
        }
        SoundManager::PlaySoundEffect("attack");
        return new AttackBossState();
    }

    return this;
}

IBossState* AttackBossState::Update(Boss& boss)
{
    boss.current = Attack;
    boss.attackFrame = 7;
    boss.velocity.x = 0;

    if (boss.isHurt) {
        /*boss.beingHurt();
        return new HurtBossState();*/

        boss.hurtCnt++;
        if (boss.hurtCnt > 2) {
            boss.beingHurt();
            boss.hurtCnt = 0;
            return new HurtBossState();
        }
        else {
            boss.currentHp -= boss.damageTaken;
            boss.isHurt = false;
            std::cout << boss.currentHp << std::endl;
        }
    }

    if (boss.animationManger.IsDone() && !boss.isInAttackZone()) {
        boss.velocity.x = !boss.animationManger.IsFlip() ? -boss.moveSpeed : boss.moveSpeed;
        return new WalkBossState();
    }

    return this;
}

IBossState* DeathBossState::Update(Boss& boss)
{
    boss.current = Death;
    boss.velocity.x = 0;

    if (boss.animationManger.IsDone()) {
        boss.removeFromTree();
        Global.Score += boss.hp;
    }

    return this;
}
