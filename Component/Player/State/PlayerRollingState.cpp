#include "PlayerRollingState.h"
#include <GameObject.h>
#include <Components/AudioSource.h>
#include <Components/Camera.h>
#include <Components/Rigidbody.h>
#include <Components/Transform.h>
#include <GLGUI.h>

#include "../../Common/Rotator.h"
#include "../../Common/Damageable.h"
#include "../PlayerInput.h"
#include "../../Constant/GameObjectName.h"
#include "../../Enum/State/PlayerState.h"
#include "../../Utility/CameraUtility.h"
#include "../../Utility/RigidbodyUility.h"

using namespace Glib;

PlayerRollingState::PlayerRollingState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void PlayerRollingState::OnInitialize()
{
    const auto& camera = GameObjectManager::Find(ObjectName::Camera);
    camera_ = camera->Transform();
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
    audio_ = GameObject()->GetComponent<AudioSource>();
    rotator_ = GameObject()->GetComponent<Rotator>();
    input_ = GameObject()->GetComponent<PlayerInput>();
    damageable_ = GameObject()->GetComponent<Damageable>();
}

void PlayerRollingState::OnEnter()
{
    rotator_->Direction(CameraUtility::ConvertToCameraView(camera_, input_->Move()));
    RigidbodyUtility::KillXZVelocity(rigidbody_);
}

int PlayerRollingState::OnFixedUpdate(float elapsedTime)
{
    Move(elapsedTime <= parameter_.dodgeDuration);
    damageable_->Invincible(parameter_.invincibleTimer.Reception(elapsedTime));
    if (elapsedTime >= parameter_.dodgeDuration)
    {
        return PlayerState::Moving;
    }
    return STATE_MAINTAIN;
}

void PlayerRollingState::Move(bool moving)
{
    Vector3 velocity = moving ?
        GameObject()->Transform()->Forward().Normalized() * parameter_.moveSpeed :
        Vector3::Zero();

    Vector3 ignoreYVelocity = Vector3::Scale(rigidbody_->LinearVelocity(), Vector3{ 1.0f, 0.0f, 1.0f });
    rigidbody_->AddForce(parameter_.moveForceMultiplier * (velocity - ignoreYVelocity));
}

void PlayerRollingState::OnGUI()
{
    Component::OnGUI();
    GLGUI::DragFloat("Duration", &parameter_.dodgeDuration, 0.01f, 0.0f);
    GLGUI::DragFloat("MoveSpeed", &parameter_.moveSpeed, 0.1f);
    GLGUI::DragFloat("MoveForce", &parameter_.moveForceMultiplier, 0.1f);
}
