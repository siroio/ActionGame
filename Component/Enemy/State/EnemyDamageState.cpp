#include "EnemyDamageState.h"
#include <Components/Rigidbody.h>
#include <GameObject.h>
#include <Vector3.h>
#include <GLGUI.h>

#include "../../Enemy/CharacterSearcher.h"
#include "../../../Utility/RigidbodyUility.h"

using namespace Glib;

EnemyDamageState::EnemyDamageState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void EnemyDamageState::OnInitialize()
{
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
    searcher_ = GameObject()->GetComponent<CharacterSearcher>();
}

void EnemyDamageState::OnEnter()
{
    RigidbodyUtility::KillXZVelocity(rigidbody_);
}

void EnemyDamageState::OnExit()
{
    RigidbodyUtility::KillXZVelocity(rigidbody_);
}

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
    Vector3 direction;
    if (!searcher_->Target().expired())
    {
        // ターゲットがいたらターゲットと逆方向へ移動
        direction = GameObject()->Transform()->Position() - searcher_->Target()->Transform()->Position();
    }
    else
    {
        // ターゲットがいなかったら後ろ方向へ移動
        direction = -GameObject()->Transform()->Forward();
    }
    return parameter_.moveSpeed * direction;
}

void EnemyDamageState::OnGUI()
{
    GLGUI::DragFloat("Duration", &parameter_.duration, 0.01f);
    GLGUI::DragFloat("MoveSpeed", &parameter_.moveSpeed, 0.1f);
    GLGUI::DragFloat("MoveForce", &parameter_.moveForceMultiplier, 0.1f);
}
