#include "EnemyAttackState.h"
#include <Components/Rigidbody.h>
#include <GameObject.h>
#include <GLGUI.h>

#include "../../Common/AttackColliderController.h"
#include "../../../Utility/RigidbodyUility.h"

using namespace Glib;

EnemyAttackState::EnemyAttackState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void EnemyAttackState::OnInitialize()
{
    attackCollider_ = GameObject()->GetComponentInChildren<AttackColliderController>();
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
}

void EnemyAttackState::OnEnter()
{
    // 攻撃力を設定
    attackCollider_->SetAttackPower(parameter_.power);
    RigidbodyUtility::KillXZVelocity(rigidbody_);
}

int EnemyAttackState::OnUpdate(float elapsedTime)
{
    const bool& isAttack = parameter_.attackTime.Reception(elapsedTime);
    attackCollider_->SetAttackActive(isAttack);
    if (elapsedTime >= parameter_.duration)
    {
        return parameter_.nextStateID;
    }
    return STATE_MAINTAIN;
}

void EnemyAttackState::OnExit()
{
    attackCollider_->SetAttackActive(false);
    attackCollider_->SetAttackPower(0);
}

void EnemyAttackState::OnGUI()
{
    GLGUI::DragInt("Power", &parameter_.power);
    GLGUI::DragFloat("Duration", &parameter_.duration);
}
