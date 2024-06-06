#include "PlayerInput.h"
#include <InputSystem.h>
#include <Vector2.h>
#include "../../Constant/ButtonName.h"

using namespace Glib;

bool PlayerInput::Pose() const
{
    return InputSystem::GetInputDown(ButtonName::POSE) && enable_;
}

bool PlayerInput::Comfirm() const
{
    return InputSystem::GetInputDown(ButtonName::CONFIRM) && enable_;
}

bool PlayerInput::Deny() const
{
    return InputSystem::GetInputDown(ButtonName::DENY) && enable_;
}

bool PlayerInput::Up() const
{
    return InputSystem::GetInputDown(ButtonName::UP) && enable_;
}

bool PlayerInput::Down() const
{
    return InputSystem::GetInputDown(ButtonName::DOWN) && enable_;
}

bool PlayerInput::Attack() const
{
    return InputSystem::GetInputDown(ButtonName::ATTACK) && enable_;
}

bool PlayerInput::Dodge() const
{
    return InputSystem::GetInputDown(ButtonName::DODGE) && enable_;
}

Vector2 PlayerInput::Camera() const
{
    return enable_ ? InputSystem::GetRightStick() : Vector2::Zero();
}

Vector2 PlayerInput::Move() const
{
    return enable_ ? InputSystem::GetLeftStick() : Vector2::Zero();
}

void PlayerInput::InputEnable(bool enable)
{
    enable_ = enable;
}
