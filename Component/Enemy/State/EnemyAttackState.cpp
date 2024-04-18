#include "EnemyAttackState.h"

EnemyAttackState::EnemyAttackState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void EnemyAttackState::OnEnter()
{

}

int EnemyAttackState::OnUpdate(float elapsedTime)
{
    return STATE_MAINTAIN;
}

void EnemyAttackState::OnExit()
{

}
