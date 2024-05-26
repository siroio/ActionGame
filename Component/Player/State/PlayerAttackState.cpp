#include "PlayerAttackState.h"
#include <GameObject.h>
#include <Components/AudioSource.h>
#include <Components/Camera.h>
#include <Components/Rigidbody.h>
#include <Components/Transform.h>
#include <Components/EffectSystem.h>
#include <Random.h>
#include <GLGUI.h>

#include "../../Common/Rotator.h"
#include "../../Common/AttackColliderController.h"
#include "../../Common/DelayedAudioPlayer.h"
#include "../PlayerInput.h"
#include "../../Constant/GameObjectName.h"
#include "../../Enum/State/PlayerState.h"
#include "../../Utility/CameraUtility.h"
#include "../../Utility/RigidbodyUility.h"

using namespace Glib;

namespace
{
    const Vector2 SE_PITCH_RANGE{ 0.8f, 1.2f };
    constexpr float SE_DELAY{ 0.15f };
}

PlayerAttackState::PlayerAttackState(const Parameter& parameter, const WeakPtr<EffectSystem>& slash) :
    parameter_{ parameter }, slashEfk_{ slash }
{}

void PlayerAttackState::OnInitialize()
{
    const auto& camera = GameObjectManager::Find(ObjectName::Camera);
    camera_ = camera->Transform();
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
    audio_ = GameObject()->GetComponent<DelayedAudioPlayer>();
    rotator_ = GameObject()->GetComponent<Rotator>();
    input_ = GameObject()->GetComponent<PlayerInput>();
    attackCollider_ = GameObject()->GetComponentInChildren<AttackColliderController>();
}

void PlayerAttackState::OnEnter()
{
    if (!slashEfk_.expired()) slashEfk_->Play();
    audio_->SetClip(parameter_.attackSEID);
    audio_->SetPitch(Random::Range(SE_PITCH_RANGE.x, SE_PITCH_RANGE.y));
    audio_->Play(SE_DELAY);
    rotator_->Direction(CameraUtility::ConvertToCameraView(camera_, input_->Move()));
    attackCollider_->SetAttackPower(parameter_.power);
    RigidbodyUtility::KillXZVelocity(rigidbody_);
}

void PlayerAttackState::OnExit()
{
    if (!slashEfk_.expired()) slashEfk_->Stop();
    attackCollider_->SetAttackPower(0);
    attackCollider_->SetAttackActive(false);
    RigidbodyUtility::KillXZVelocity(rigidbody_);
}

int PlayerAttackState::OnUpdate(float elapsedTime)
{
    if (IsAttack(elapsedTime))
    {
        return parameter_.nextAttackState;
    }

    if (IsTimeOver(elapsedTime))
    {
        return PlayerState::Moving;
    }

    attackCollider_->SetAttackActive(EnableAttack(elapsedTime));

    return STATE_MAINTAIN;
}

int PlayerAttackState::OnFixedUpdate(float elapsedTime)
{
    Move(elapsedTime);
    return STATE_MAINTAIN;
}

bool PlayerAttackState::IsAttack(float elapsedTime)
{
    return parameter_.inputTimer.Reception(elapsedTime) && input_->Attack();
}

bool PlayerAttackState::EnableAttack(float elapsedTime)
{
    return parameter_.colliderTimer.Reception(elapsedTime);
}

bool PlayerAttackState::IsTimeOver(float elapsedTime) const
{
    float endTime{
        parameter_.inputTimer.ReceptionTime() +
        parameter_.inputTimer.StartTime() +
        parameter_.stateEndTime
    };
    return elapsedTime >= endTime;
}

void PlayerAttackState::Move(float elapsedTime)
{
    bool isMove = elapsedTime <= parameter_.moveDuration;
    Vector3 velocity = RigidbodyUtility::GetMoveVelocity(rigidbody_, parameter_.moveForceMultiplier, MoveSpeed(isMove));
    rigidbody_->AddForce(velocity);
}

Vector3 PlayerAttackState::MoveSpeed(bool moving)
{
    return moving ?
        GameObject()->Transform()->Forward().Normalized() * parameter_.moveSpeed :
        Vector3::Zero();
}

void PlayerAttackState::OnGUI()
{
    float moveDuration{ parameter_.moveDuration };
    if (GLGUI::DragFloat("MoveTime", &moveDuration, 0.001f))
    {
        parameter_.moveDuration = moveDuration;
    }

    float moveSpeed{ parameter_.moveSpeed };
    if (GLGUI::DragFloat("MoveSpeed", &moveSpeed, 0.01f))
    {
        parameter_.moveSpeed = moveSpeed;
    }

    float moveForce{ parameter_.moveForceMultiplier };
    if (GLGUI::DragFloat("MoveForce", &moveForce, 0.01f))
    {
        parameter_.moveForceMultiplier = moveForce;
    }

    if (GLGUI::TreeNode("ATK Parameter"))
    {
        GLGUI::InputInt("NextState", &parameter_.nextAttackState);
        GLGUI::InputInt("AttackSEID", &parameter_.attackSEID);
        GLGUI::InputInt("AttackPower", &parameter_.power);
        GLGUI::DragFloat("AttackEndTime", &parameter_.stateEndTime, 0.01f);

        ValidityTimer& timer = parameter_.inputTimer;

        float startTime = timer.StartTime();
        if (GLGUI::DragFloat("StartTime", &startTime, 0.01f))
        {
            timer.StartTime(startTime);
        }

        float receptionTime = timer.ReceptionTime();
        if (GLGUI::DragFloat("ReceptionTime", &receptionTime, 0.01f))
        {
            timer.ReceptionTime(receptionTime);
        }

        GLGUI::TreePop();
    }
}
