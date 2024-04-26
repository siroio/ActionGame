#include "CameraRotator.h"
#include <GameObject.h>
#include <Components/Transform.h>
#include <GameTimer.h>
#include <GLGUI.h>
#include <Mathf.h>

#include "../../Input/Input.h"
#include "../Camera/CameraController.h"

using namespace Glib;

void CameraRotator::Start()
{
    controller_ = GameObject()->GetComponent<CameraController>();
}

void CameraRotator::FixedUpdate()
{
    Rotate();
}

Vector3 euler;

void CameraRotator::Rotate()
{
    const auto& transform = GameObject()->Transform();
    CameraController::Parameter parameter = controller_->GetParameter();
    const float deltaTime = GameTimer::FixedDeltaTime();

    Vector2 angle = Input::CameraRotate() * rotateSpeed_;

    euler.x -= angle.y * deltaTime;
    euler.y += angle.x * deltaTime;

    if (euler.x > 180.0f) euler.x -= 360.0f;
    euler.x = Mathf::Clamp(euler.x, angleLimitNegativeX, angleLimitPositiveX);
    parameter.Angle = euler;
    controller_->SetParameter(parameter);
}

void CameraRotator::OnGUI()
{
    Component::OnGUI();
    float rotateSpeed{ rotateSpeed_ };
    if (GLGUI::DragFloat("RotateSpeed", &rotateSpeed, 0.1f, 0.0f))
    {
        rotateSpeed_ = rotateSpeed;
    }
    if (GLGUI::TreeNode("AngleLimit"))
    {
        GLGUI::DragFloat("Min", &angleLimitNegativeX, 0.1f, -90.0f, angleLimitPositiveX);
        GLGUI::DragFloat("Max", &angleLimitPositiveX, 0.1f, angleLimitNegativeX, 90.0f);
        GLGUI::TreePop();
    }
}
