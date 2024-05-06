#include "EnemyDeadState.h"
#include <Components/Rigidbody.h>
#include <GameObject.h>

#include "../../Character/DeadEffect/EnemyDeadEffect.h"
#include "../../../Utility/RigidbodyUility.h"

using namespace Glib;

EnemyDeadState::EnemyDeadState(float duration) :
    duration_{ duration }
{}

void EnemyDeadState::OnInitialize()
{
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
}

void EnemyDeadState::OnEnter()
{
    //死亡したメッセージを飛ばす
    RigidbodyUtility::KillXZVelocity(rigidbody_);
}

int EnemyDeadState::OnUpdate(float elapsedTime)
{
    if (elapsedTime >= duration_)
    {
        GameObject()->Destroy();
        // 死亡時のエフェクトを出す
        const auto& position = GameObject()->Transform()->Position();
        EnemyDeadEffect::Spawn(position);
    }
    return STATE_MAINTAIN;
}
