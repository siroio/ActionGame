#include "PlayerMoveState.h"
#include <Components/Transform.h>
#include <Components/Rigidbody.h>
#include <Components/Animator.h>
#include <GameObjectManager.h>
#include <GameObject.h>
#include <InputSystem.h>
#include <Physics.h>
#include <RaycastHit.h>
#include <GameTimer.h>
#include <Vector3.h>
#include <Vector2.h>
#include <Mathf.h>
#include <Debugger.h>
#include <Color.h>
#include <GLGUI.h>
#include <vector>

#include "../../Constant/GameObjectName.h"
#include "../../Constant/ButtonName.h"
#include "../../Enum/State/PlayerState.h"
#include "../../Enum/AnimationID.h"
#include "../../Utility/CameraUtility.h"
#include "../../Utility/RigidbodyUility.h"
#include "../PlayerInput.h"

using namespace Glib;

PlayerMoveState::PlayerMoveState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void PlayerMoveState::OnInitialize()
{
    const auto& camera = GameObjectManager::Find(ObjectName::Camera);
    camera_ = camera->Transform();
    animator_ = GameObject()->GetComponent<Animator>();
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
    rotator_ = GameObject()->GetComponent<Rotator>();
    input_ = GameObject()->GetComponent<PlayerInput>();
}

int PlayerMoveState::OnUpdate(float elapsedTime)
{
    if (InputSystem::GetInput(ButtonName::ATTACK))
    {
        return PlayerState::Attack1;
    }

    if (InputSystem::GetInput(ButtonName::DODGE))
    {
        return PlayerState::Rolling;
    }

    moveInput_ = CameraUtility::ConvertToCameraView(camera_, input_->Move());
    return STATE_MAINTAIN;
}

int PlayerMoveState::OnFixedUpdate(float elapsedTime)
{
    Move();
    return STATE_MAINTAIN;
}

void PlayerMoveState::Move()
{
    const auto& transform = GameObject()->Transform();

    // 操作方向へ回転
    rotator_->Direction(moveInput_);
    Vector3 velocity = moveInput_ * parameter_.moveSpeed;
    ChangeAnimation(velocity.SqrMagnitude() > Mathf::EPSILON);

    velocity = RigidbodyUtility::GetMoveVelocity(rigidbody_, parameter_.moveForceMultiplier, velocity);
    rigidbody_->AddForce(velocity);
}

void PlayerMoveState::ChangeAnimation(bool moving)
{
    const auto& info = moving ? parameter_.walkInfo : parameter_.idleInfo;
    if (animator_->AnimationID() == info.AnimationID) return;
    SetAnimationInfo(info);
    SetAnimation(animator_);
}

void PlayerMoveState::OnGUI()
{
    Component::OnGUI();
    float moveSpeed{ parameter_.moveSpeed };
    if (GLGUI::DragFloat("MoveSpeed", &moveSpeed, 0.1f))
    {
        parameter_.moveSpeed = moveSpeed;
    }

    float moveForceMultiplier{ parameter_.moveForceMultiplier };
    if (GLGUI::DragFloat("MoveForce", &moveForceMultiplier, 0.1f))
    {
        parameter_.moveForceMultiplier = moveForceMultiplier;
    }
}
