#include "IEnemyState.h"

IEnemyState* IdleEnemyState::Update(Enemy& enemy)
{
    enemy.current = Idle;
    
    enemy.velocity.x = 0;

    if (enemy.isHurt) {
        enemy.beingHurt();
        return new HurtEnemyState();
    }

    if (enemy.isInEnemyZone()) {
        if (enemy.isInAttackZone()) return new AttackEnemyState();
        if (enemy.isEdge() && !enemy.checkTurn() || enemy.isHitWall() && !enemy.checkTurn()) return this;
        return new RunEnemyState();
    }

    enemy.timer += Global.DeltaTime;
    if (enemy.timer >= enemy.timeChangeState) {
        enemy.timer = 0;
        return new RunEnemyState();
    }

    
    return this;
}

IEnemyState* RunEnemyState::Update(Enemy& enemy)
{
    enemy.current = Run;
    enemy.velocity.x = enemy.animationManger.IsFlip() ? -enemy.moveSpeed : enemy.moveSpeed;

    if (enemy.isInEnemyZone()) {
        enemy.velocity.x = enemy.center_pos.x < enemy.player->center_pos.x ? enemy.moveSpeed : -enemy.moveSpeed;
        if (enemy.isEdge() || enemy.isHitWall()) return new IdleEnemyState;
        if (enemy.isInAttackZone()) return new AttackEnemyState();
    }


    if (enemy.timer >= enemy.timeChangeState) {
        enemy.timer = 0;
        return new IdleEnemyState();
    }
    if (enemy.isEdge() || enemy.isHitWall()) enemy.velocity.x *= -1;

    if (enemy.isHurt) {
        enemy.beingHurt();
        return new HurtEnemyState();
    }

    enemy.timer += Global.DeltaTime;

    return this;
}

IEnemyState* DeathEnemyState::Update(Enemy& enemy)
{
    enemy.current = Death;
    enemy.velocity.x = 0;
    if (enemy.animationManger.IsDone()) {
        Global.Score += enemy.hp;
        enemy.removeFromTree();
    }
    return this;
}

IEnemyState* HurtEnemyState::Update(Enemy& enemy)
{
    enemy.current = Hurt;
    enemy.velocity.x = enemy.moveSpeed/2 * enemy.hurtDirection;

    //if (enemy.isHurt) {
    //    //enemy.beingHurt();
    //    return new HurtEnemyState();
    //}

    if (enemy.animationManger.IsDone()) {
        if (enemy.currentHp <= 0) {
            enemy.current = Death;
            return new DeathEnemyState();
        }
        return new IdleEnemyState();
    }
    return this;
}

IEnemyState* AttackEnemyState::Update(Enemy& enemy)
{
    enemy.current = Attack;
    enemy.attackFrame = 6;
    enemy.velocity.x = 0;

    if (enemy.isHurt) {
        enemy.beingHurt();
        return new HurtEnemyState();
    }

    if (enemy.animationManger.IsDone() && !enemy.isInAttackZone()) {
        enemy.velocity.x = enemy.animationManger.IsFlip() ? -enemy.moveSpeed : enemy.moveSpeed;
        return new RunEnemyState();
    }

    return this;
}
