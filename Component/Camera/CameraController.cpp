#include "CameraController.h"
#include <GameObjectManager.h>
#include <GameObject.h>
#include <GameTimer.h>
#include <Mathf.h>
#include <Easing.h>
#include <Physics.h>
#include <RaycastHit.h>
#include <GLGUI.h>
#include <Debugger.h>

#include "../../Constant/CameraConstant.h"
#include "../../Constant/GameObjectName.h"
#include "../../Constant/ObjectTag.h"

using namespace Glib;

CameraController::CameraController(const CameraController::Parameter& parameter) :
    parameter_{ parameter }
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
    parent_ = GameObject()->Transform();
    child_ = parent_->Find("Camera Child");
    camera_ = parent_->Find("Camera");
}

void CameraController::FixedUpdate()
{
    if (parent_.expired() || child_.expired() || camera_.expired()) return;

    if (!parameter_.Target.expired())
    {
        const float speed = parameter_.FollowSpeed * GameTimer::FixedDeltaTime();
        parameter_.Position = Vector3::Lerp(
            parameter_.Position,
            parameter_.Target->Position(),
            Easing::Evaluate(Ease::OutQuart, speed)
        );
    }

    parent_->Position(parameter_.Position);
    parent_->EulerAngles(parameter_.Angle);

    Vector3 childPoition = child_->LocalPosition();
    childPoition.z = -parameter_.Distance;
    child_->LocalPosition(childPoition);

    camera_->LocalPosition(parameter_.Offset);
    camera_->LocalEulerAngles(parameter_.OffsetAngle);

    if (parameter_.ObstacleDetection && !parameter_.Target.expired())
    {
        ObstacleDetection();
    }
}

void CameraController::SetTarget(const WeakPtr<Transform>& target)
{
    parameter_.Target = target;
}

CameraController::Parameter CameraController::GetParameter() const
{
    return parameter_;
}

void CameraController::SetParameter(const Parameter& parameter)
{
    parameter_ = parameter;
}

void CameraController::ObstacleDetection()
{
    const auto& target = parameter_.Target;
    const Vector3& direction = camera_->Rotation() * Vector3::Back();

    // 注目対象からの方向
    std::vector<RaycastHit> hits{};
    if (!Physics::RaycastAll(target->Position() + parameter_.Offset, direction, hits, parameter_.Distance)) return;

    float shortestPath = parameter_.Distance * parameter_.Distance;
    for (const auto& hit : hits)
    {
        if (hit.gameObject.expired()) continue;
        if (hit.gameObject->Tag() != GameTag::OBSTACLE) continue;
        Vector3 nearestPoint = target->InverseTransformPoint(hit.point);
        const float& distSqr = nearestPoint.SqrMagnitude();
        if (distSqr < shortestPath)
        {
            shortestPath = distSqr;
            parameter_.Position = hit.point - (direction * 0.01f);
        }
    }

}

void CameraController::OnGUI()
{
    Component::OnGUI();

    Vector3 position{ parameter_.Position };
    if (GLGUI::DragVector3("Position", &position, 0.1f, 0.0f))
    {
        parameter_.Position = position;
    }

    Vector3 angle{ parameter_.Angle };
    if (GLGUI::DragVector3("Angle", &angle, 0.1f, 0.0f))
    {
        parameter_.Angle = angle;
    }

    Vector3 offset{ parameter_.Offset };
    if (GLGUI::DragVector3("Offset", &offset, 0.1f))
    {
        parameter_.Offset = offset;
    }

    Vector3 offsetAngle{ parameter_.OffsetAngle };
    if (GLGUI::DragVector3("OffsetAngle", &offsetAngle, 0.1f))
    {
        parameter_.OffsetAngle = offsetAngle;
    }

    float distance{ parameter_.Distance };
    if (GLGUI::DragFloat("Distance", &distance, 0.1f))
    {
        parameter_.Distance = distance;
    }

    float followSpeed{ parameter_.FollowSpeed };
    if (GLGUI::DragFloat("FollowSpeed", &followSpeed, 0.1f))
    {
        parameter_.FollowSpeed = followSpeed;
    }

    float rotateSpeed{ parameter_.RotateSpeed };
    if (GLGUI::DragFloat("RotateSpeed", &rotateSpeed, 0.1f))
    {
        parameter_.RotateSpeed = rotateSpeed;
    }
}
