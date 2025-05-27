#include "IEnemyState.h"

IEnemyState* IdleEnemyState::Update(Enemy& enemy)
{
    enemy.current = Idle;
    enemy.timer += Global.DeltaTime;

    if (enemy.timer >= enemy.timeChangeState) {
        enemy.timer = 0;
        enemy.velocity.x = enemy.animationManger.IsFlip() ? -enemy.moveSpeed : enemy.moveSpeed;
        return new RunEnemyState();
    }

    

    return this;
}

IEnemyState* RunEnemyState::Update(Enemy& enemy)
{
    enemy.current = Run;
    enemy.timer += Global.DeltaTime;

    if (enemy.timer >= enemy.timeChangeState) {
        enemy.timer = 0;
        enemy.velocity.x = 0;
        return new IdleEnemyState();
    }
    if (enemy.isEdge()) enemy.velocity.x *= -1;

    return this;
}
