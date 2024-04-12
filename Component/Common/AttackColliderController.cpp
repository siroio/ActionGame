#include "AttackColliderController.h"
#include <Components/BoxCollider.h>
#include <GameObject.h>
#include <Debugger.h>
using namespace Glib;

void AttackColliderController::Start()
{
    collider_ = GameObject()->GetComponent<BoxCollider>();
}

void AttackColliderController::SetAttckActive(bool enable)
{
    collider_->Active(enable);
}

void AttackColliderController::OnTriggerEnter(const GameObjectPtr& other)
{
    if (other.expired()) return;
}
