#include "EnemyProjectileAttackState.h"
#include <GameObject.h>
#include <Random.h>

#include "../../StateMachine/StateBehavior.h"
#include "../../Enemy/CharacterSearcher.h"

EnemyProjectileAttackState::EnemyProjectileAttackState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void EnemyProjectileAttackState::OnEnter()
{
    attacked_ = false;
}

void EnemyProjectileAttackState::OnInitialize()
{
    stateBehavior_ = GameObject()->GetComponent<StateBehavior>();
    searcher_ = GameObject()->GetComponent<CharacterSearcher>();
}

int EnemyProjectileAttackState::OnUpdate(float elapsedTime)
{
    if (elapsedTime >= parameter_.duration)
    {
        return parameter_.nextStateID;
    }
    if (elapsedTime >= parameter_.delay)
    {
        Attack();
    }
    return STATE_MAINTAIN;
}

void EnemyProjectileAttackState::Attack()
{
    if (attacked_) return;
    if (searcher_.expired() || parameter_.spawn == nullptr) return;

    attacked_ = true;
    const auto& offsetPoint = parameter_.spawnPoint;
    const auto& position = GameObject()->Transform()->Position();

    // 生成
    parameter_.spawn(position + offsetPoint, parameter_.flySpeed, searcher_->Target());
}
