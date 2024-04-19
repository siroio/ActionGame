#include "PlayerMoveState.h"
#include <Components/Transform.h>
#include <Components/Rigidbody.h>
#include <Components/Animator.h>
#include <GameObjectManager.h>
#include <GameObject.h>
#include <Physics.h>
#include <RaycastHit.h>
#include <GameTimer.h>
#include <Vector3.h>
#include <Mathf.h>
#include <Debugger.h>
#include <Color.h>
#include <GLGUI.h>
#include <vector>

#include "../../Enum/State/PlayerState.h"
#include "../../Enum/AnimationID.h"
#include "../../Input/Input.h"
#include "../../Utility/Enum.h"
#include "../../Utility/CameraUtility.h"
#include "../../Utility/RigidbodyUility.h"

using namespace Glib;

PlayerMoveState::PlayerMoveState(const Parameter& parameter) :
    parameter_{ parameter }
{}

void PlayerMoveState::OnInitialize()
{
    const auto& camera = GameObjectManager::Find("Camera Parent");
    camera_ = camera->Transform();
    animator_ = GameObject()->GetComponent<Animator>();
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
    rotator_ = GameObject()->GetComponent<Rotator>();
}

int PlayerMoveState::OnUpdate(float elapsedTime)
{
    if (Input::Attack())
    {
        return PlayerState::Attack1;
    }

    if (Input::Dodge())
    {
        return PlayerState::Rolling;
    }

    moveInput_ = CameraUtility::ConvertToCameraView(camera_, Input::Move());
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

    std::vector<RaycastHit> hits{};
    if (Physics::RaycastAll(transform->Position(), Vector3::Down(), hits, 1.0f))
    {
        // 地面を検索
        const auto& hit{ std::ranges::find_if(hits, [](const RaycastHit& hit)
        {
            return hit.gameObject->Tag() == "Ground";
        }) };

        if (hit != hits.end()) moveInput_ = Vector3::ProjectOnPlane(moveInput_, hit->normal).Normalized();
    }

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
