#include "AttackColliderController.h"
#include <Components/Collider.h>
#include <GameObject.h>

#include "../../Enum/MessageID.h"
#include "Damageable.h"

using namespace Glib;

AttackColliderController::AttackColliderController(bool onHitDestroy) :
    onHitDestroy_{ onHitDestroy }
{}

void AttackColliderController::AddCollider(const Glib::WeakPtr<Glib::Collider>& collider)
{
    colliders_.push_back(collider);
}

void AttackColliderController::SetAttackActive(bool enable)
{
    for (const auto& collider : colliders_)
    {
        collider->Active(enable);
    }
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

    // 当たった時にオブジェクトを破棄するか
    if (onHitDestroy_)
    {
        for (const auto& collider : colliders_)
        {
            collider->GameObject()->Destroy();
        }
    }
}
