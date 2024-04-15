#include "AttackColliderController.h"
#include <Components/Collider.h>
#include <GameObject.h>
#include "Damageable.h"

using namespace Glib;

AttackColliderController::AttackColliderController(const WeakPtr<Collider>& collider) :
    collider_{ collider }
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
    damageable->TakeDamage(power_);
}
