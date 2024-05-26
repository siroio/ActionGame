#include "PlayerInput.h"
#include <Vector2.h>
#include <InputSystem.h>

#include "../../Constant/ButtonName.h"

using namespace Glib;

bool PlayerInput::Pose()
{
    return InputSystem::GetInputDown(ButtonName::POSE);
}

bool PlayerInput::Comfirm()
{
    return InputSystem::GetInputDown(ButtonName::CONFIRM);
}

bool PlayerInput::Deny()
{
    return InputSystem::GetInputDown(ButtonName::DENY);
}

bool PlayerInput::Up()
{
    return InputSystem::GetInputDown(ButtonName::UP);
}

bool PlayerInput::Down()
{
    return InputSystem::GetInputDown(ButtonName::DOWN);
}

bool PlayerInput::Attack()
{
    return InputSystem::GetInputDown(ButtonName::ATTACK);
}

bool PlayerInput::Dodge()
{
    return InputSystem::GetInputDown(ButtonName::DODGE);
}

Vector2 PlayerInput::Camera()
{
    return InputSystem::GetRightStick();
}

Vector2 PlayerInput::Move()
{
    return InputSystem::GetLeftStick();
}
