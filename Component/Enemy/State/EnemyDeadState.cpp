#include "EnemyDeadState.h"
#include <GameObject.h>

EnemyDeadState::EnemyDeadState(float duration) :
    duration_{ duration }
{}

void EnemyDeadState::OnEnter()
{
    //死亡したメッセージを飛ばす
}

int EnemyDeadState::OnUpdate(float elapsedTime)
{
    if (elapsedTime >= duration_)
    {
        GameObject()->Destroy();
        // TODO: 死亡時のエフェクトを出す
    }
    return STATE_MAINTAIN;
}
