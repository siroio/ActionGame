#include "EnemyChaseState.h"
#include <Components/Transform.h>
#include <Components/Rigidbody.h>
#include <GameObject.h>

#include "../../../Utility/RigidbodyUility.h"
#include "../../Common/Rotator.h"
#include "../CharacterSearcher.h"

using namespace Glib;

void EnemyChaseState::OnInitialize()
{
    rigibody_ = GameObject()->GetComponent<Rigidbody>();
    searcher_ = GameObject()->GetComponent<CharacterSearcher>();
    rotator_ = GameObject()->GetComponent<Rotator>();
}

int EnemyChaseState::OnFixedUpdate(float eplasedTime)
{
    Move();
    return STATE_MAINTAIN;
}

void EnemyChaseState::Move()
{
    const auto& toTarget = ToTargetDistance().Normalized();
    rotator_->Direction(toTarget);
    rigibody_->AddForce(MoveSpeed(toTarget));
}

bool EnemyChaseState::CompleteMove()
{
    const auto& distance = ToTargetDistance();
    return distance.Magnitude() <= parameter_.completeDistance;
}

Vector3 EnemyChaseState::ToTargetDistance()
{
    if (searcher_->Target().expired()) return Vector3::Zero();
    Vector3 target = searcher_->Target()->Transform()->Position();
    Vector3 self = GameObject()->Transform()->Position();

    // 高さを無視
    target.y = 0.0f;
    self.y = 0.0f;
    return target - self;
}

Vector3 EnemyChaseState::MoveSpeed(const Vector3& direction)
{
    return RigidbodyUtility::GetMoveVelocity(rigibody_, parameter_.moveForceMultiplier, direction * parameter_.moveSpeed);
}
