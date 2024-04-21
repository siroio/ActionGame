#include "EnemyAttackState.h"
#include <GameObject.h>
#include <GLGUI.h>
#include "../../Common/AttackColliderController.h"

using namespace Glib;

EnemyAttackState::EnemyAttackState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void EnemyAttackState::OnInitialize()
{
    attackCollider = GameObject()->GetComponent<AttackColliderController>();
}

void EnemyAttackState::OnEnter()
{
    // 攻撃力を設定
    attackCollider->SetAttackPower(parameter_.power);
}

int EnemyAttackState::OnUpdate(float elapsedTime)
{
    const bool& isAttack = parameter_.attackTime.Reception(elapsedTime);
    attackCollider->SetAttackActive(isAttack);
    if (parameter_.duration >= elapsedTime)
    {
        return parameter_.nextStateID;
    }
    return STATE_MAINTAIN;
}

void EnemyAttackState::OnExit()
{
    attackCollider->SetAttackActive(false);
}

void EnemyAttackState::OnGUI()
{
    GLGUI::DragInt("Power", &parameter_.power);
    GLGUI::DragFloat("Duration", &parameter_.duration);
}
