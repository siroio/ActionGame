#include "EnemyDamageState.h"
#include <Components/Rigidbody.h>
#include <GameObject.h>
#include <Vector3.h>

#include "../../Common/Damageable.h"
#include "../../../Utility/RigidbodyUility.h"

using namespace Glib;

EnemyDamageState::EnemyDamageState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void EnemyDamageState::OnInitialize()
{
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
}

void EnemyDamageState::OnEnter()
{
    RigidbodyUtility::KillXZVelocity(rigidbody_);
}

void EnemyDamageState::OnExit()
{}

int EnemyDamageState::OnUpdate(float elapsedTime)
{
    if (elapsedTime >= parameter_.duration)
    {
        return parameter_.nextStateID;
    }
    return STATE_MAINTAIN;
}

int EnemyDamageState::OnFixedUpdate(float elapsedTime)
{
    Move();
    return STATE_MAINTAIN;
}

void EnemyDamageState::Move()
{
    const Vector3 velocity = RigidbodyUtility::GetMoveVelocity(rigidbody_, parameter_.moveForceMultiplier, GetFlinchVelocity());
    rigidbody_->AddForce(velocity);
}

Vector3 EnemyDamageState::GetFlinchVelocity() const
{
    return parameter_.moveSpeed * (GameObject()->Transform()->Rotation() * Vector3::Back());
}

void EnemyDamageState::OnGUI()
{}
