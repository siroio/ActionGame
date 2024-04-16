#include "CameraController.h"

#include "../../Constant/CameraConstant.h"
#include "../../Constant/GameObjectName.h"
#include <GameObjectManager.h>
#include <GameObject.h>
#include <GameTimer.h>
#include <Mathf.h>
#include <Easing.h>
#include <GLGUI.h>

using namespace Glib;


CameraController::CameraController(const CameraController::Parameter& parameter) :
    params_{ parameter }
{}

Vector3 CameraController::LerpAngle(const Vector3& a, const Vector3& b, float t)
{
    return Vector3{
        Mathf::LerpAngle(a.x, b.x, t),
        Mathf::LerpAngle(a.y, b.y, t),
        Mathf::LerpAngle(a.z, b.z, t)
    };
}

CameraController::Parameter CameraController::Lerp(const Parameter& a, const Parameter& b, float t)
{
    Parameter param{};
    param.Position = Vector3::Lerp(a.Position, b.Position, t);
    param.Angle = LerpAngle(a.Angle, b.Angle, t);
    param.Offset = Vector3::Lerp(a.Offset, b.Offset, t);
    param.OffsetAngle = LerpAngle(a.OffsetAngle, b.OffsetAngle, t);
    param.Distance = Mathf::Lerp(a.Distance, b.Distance, t);
    param.FollowSpeed = Mathf::Lerp(a.FollowSpeed, b.FollowSpeed, t);
    return param;
}

void CameraController::Start()
{
    auto child = GameObjectManager::Find("Camera Child");
    auto camera = GameObjectManager::Find(ObjectName::Camera);
    parent_ = GameObject()->Transform();
    child_ = child->Transform();
    camera_ = camera->Transform();
}

void CameraController::FixedUpdate()
{
    if (parent_.expired() || child_.expired() || camera_.expired()) return;

    if (!params_.Target.expired())
    {
        Vector3 pivot = Vector3::Lerp(
            params_.Position,
            params_.Target->Position(),
            params_.FollowSpeed * GameTimer::FixedDeltaTime()
        );

        params_.Position = pivot;
    }

    parent_->Position(params_.Position);
    parent_->EulerAngles(params_.Angle);

    Vector3 childPoition = child_->LocalPosition();
    childPoition.z = -params_.Distance;
    child_->LocalPosition(childPoition);

    camera_->LocalPosition(params_.Offset);
    camera_->LocalEulerAngles(params_.OffsetAngle);
}

void CameraController::SetTarget(const WeakPtr<Transform>& target)
{
    params_.Target = target;
}

CameraController::Parameter CameraController::GetParameter() const
{
    return params_;
}

void CameraController::SetParameter(const Parameter& parameter)
{
    params_ = parameter;
}

void CameraController::OnGUI()
{
    Component::OnGUI();

    Vector3 position{ params_.Position };
    if (Glib::GLGUI::DragVector3("Position", &position, 0.1f, 0.0f))
    {
        params_.Position = position;
    }

    Vector3 angle{ params_.Angle };
    if (GLGUI::DragVector3("Angle", &angle, 0.1f, 0.0f))
    {
        params_.Angle = angle;
    }

    Vector3 offset{ params_.Offset };
    if (GLGUI::DragVector3("Offset", &offset, 0.1f))
    {
        params_.Offset = offset;
    }

    Vector3 offsetAngle{ params_.OffsetAngle };
    if (GLGUI::DragVector3("OffsetAngle", &offsetAngle, 0.1f))
    {
        params_.OffsetAngle = offsetAngle;
    }

    float distance{ params_.Distance };
    if (GLGUI::DragFloat("Distance", &distance, 0.1f))
    {
        params_.Distance = distance;
    }

    float followSpeed{ params_.FollowSpeed };
    if (GLGUI::DragFloat("FollowSpeed", &followSpeed, 0.1f))
    {
        params_.FollowSpeed = followSpeed;
    }

    float rotateSpeed{ params_.RotateSpeed };
    if (GLGUI::DragFloat("RotateSpeed", &rotateSpeed, 0.1f))
    {
        params_.RotateSpeed = rotateSpeed;
    }
}
