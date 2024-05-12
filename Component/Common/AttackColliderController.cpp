#include "AttackColliderController.h"
#include <Components/Collider.h>
#include <GameObject.h>

#include "../../Enum/MessageID.h"
#include "Damageable.h"

using namespace Glib;

AttackColliderController::AttackColliderController(const WeakPtr<Collider>& collider, bool onHitDestroy) :
    collider_{ collider }, onHitDestroy_{ onHitDestroy }
{}

void AttackColliderController::SetAttackActive(bool enable)
{
    collider_->Active(enable);
}

void AttackColliderController::SetAttackPower(int power)
{
    power_ = power;
}

void AttackColliderController::OnTriggerEnter(const GameObjectPtr& other)
{
    if (other.expired()) return;
    auto damageable = other->GetComponent<Damageable>();

    if (damageable.expired()) return;
    if (damageable->TakeDamage(power_))
    {
        // 攻撃成功時メッセージを送信
        // ID, 攻撃相手
        GameObject()->SendMsg(MessageID::Attacked, other);
    }

    if (onHitDestroy_)
    {
        GameObject()->Destroy();
    }
}
