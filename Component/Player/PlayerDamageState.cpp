#include "PlayerDamageState.h"
#include <GameObject.h>
#include <Components/Animator.h>
#include <Components/AudioSource.h>
#include <Components/Transform.h>
#include <Components/Rigidbody.h>
#include <GLGUI.h>

#include "../../Enum/Player/PlayerState.h"
#include "../../Utility/RigidbodyUility.h"

using namespace Glib;

PlayerDamageState::PlayerDamageState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void PlayerDamageState::OnInitialize()
{
    animator_ = GameObject()->GetComponent<Animator>();
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
    audio_ = GameObject()->GetComponent<AudioSource>();
}

void PlayerDamageState::OnEnter()
{
    animator_->AnimationID(parameter_.damageAnimID);
    RigidbodyUtility::KillXZVelocity(rigidbody_);
}

int PlayerDamageState::OnUpdate(float elapsedTime)
{
    if (elapsedTime >= parameter_.damageDuration)
    {
        return PlayerState::Moving;
    }
    return STATE_MAINTAIN;
}

int PlayerDamageState::OnFixedUpdate(float elapsedTime)
{
    Move(elapsedTime <= parameter_.damageDuration);
    return STATE_MAINTAIN;
}

void PlayerDamageState::Move(bool moving)
{
    const Vector3 velocity = RigidbodyUtility::GetMoveVelocity(rigidbody_, parameter_.moveForceMultiplier, GetFlinchVelocity());
    rigidbody_->AddForce(velocity);
}

Vector3 PlayerDamageState::GetFlinchVelocity() const
{
    return parameter_.moveSpeed * (GameObject()->Transform()->Rotation() * Vector3::Back());
}

void PlayerDamageState::OnGUI()
{
    GLGUI::DragFloat("Duration", &parameter_.damageDuration, 0.01f, 0.0f);
    GLGUI::DragFloat("MoveSpeed", &parameter_.moveSpeed, 0.1f);
    GLGUI::DragFloat("MoveForce", &parameter_.moveForceMultiplier, 0.1f);
}
