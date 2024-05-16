#include "Rotator.h"
#include <Components/Transform.h>
#include <GameObject.h>
#include <Quaternion.h>
#include <GameTimer.h>
#include <GLGUI.h>

using namespace Glib;

void Rotator::Start()
{
    transform_ = GameObject()->Transform();
}

void Rotator::Update()
{
    Quaternion targetRotation = transform_->Rotation() * Quaternion::FromToRotation(transform_->Forward(), direction_);
    float turnSpeed = turnSpeed_ * GameTimer::DeltaTime();
    Quaternion rotation = Quaternion::Slerp(transform_->Rotation(), targetRotation, turnSpeed);
    transform_->LocalRotation(rotation);
}

bool Rotator::IsCompleteRotate() const
{
    Quaternion targetRotation = transform_->Rotation() * Quaternion::FromToRotation(transform_->Forward(), direction_);
    float angle = Quaternion::Angle(transform_->Rotation(), targetRotation);
    return angle < 0.1f;// ある程度小さい角度
}

void Rotator::Direction(const Vector3& direction)
{
    direction_ = direction;
}

const Vector3& Rotator::Direction() const
{
    return direction_;
}

void Rotator::OnGUI()
{
    float turnSpeed{ turnSpeed_ };
    if (GLGUI::DragFloat("TurnSpeed", &turnSpeed, 0.1f))
    {
        turnSpeed_ = turnSpeed;
    }
}
