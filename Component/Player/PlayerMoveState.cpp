#include "PlayerMoveState.h"
#include "../../Enum/Player/PlayerState.h"
#include "../../Enum/AnimationID.h"
#include "../../Input/Input.h"
#include "../../Utility/Enum.h"
#include "../../Utility/CameraUtility.h"

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

using namespace Glib;

void PlayerMoveState::OnEnter()
{
    animator_->Loop(true);
}

void PlayerMoveState::OnInitialize()
{
    const auto& camera = GameObjectManager::Find("Camera Parent");
    camera_ = camera->Transform();
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
    animator_ = GameObject()->GetComponent<Animator>();
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

    Vector3 velocity = moveInput_ * moveSpeed_;
    unsigned int animationID{ AnimationID::PlayerIdle };
    if (velocity.SqrMagnitude() > Mathf::EPSILON) animationID = AnimationID::PlayerMove;
    ChangeAnimation(animationID);

    Vector3 ignoreYVelocity = Vector3::Scale(rigidbody_->LinearVelocity(), Vector3{ 1.0f, 0.0f, 1.0f });
    rigidbody_->AddForce(moveForceMultiplier_ * (velocity - ignoreYVelocity));
}

void PlayerMoveState::ChangeAnimation(unsigned int ID)
{
    if (ID == animator_->AnimationID()) return;
    animator_->AnimationID(ID);
}

void PlayerMoveState::OnGUI()
{
    Component::OnGUI();
    float moveSpeed{ moveSpeed_ };
    if (GLGUI::DragFloat("MoveSpeed", &moveSpeed, 0.1f))
    {
        moveSpeed_ = moveSpeed;
    }

    float moveForceMultiplier{ moveForceMultiplier_ };
    if (GLGUI::DragFloat("MoveForce", &moveForceMultiplier, 0.1f))
    {
        moveForceMultiplier_ = moveForceMultiplier;
    }
}
