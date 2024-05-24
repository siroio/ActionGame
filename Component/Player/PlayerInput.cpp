#include "PlayerInput.h"
#include <Vector2.h>
#include <InputSystem.h>

using namespace Glib;

bool PlayerInput::Pose()
{
    return false;
}

bool PlayerInput::Comfirm()
{
    return false;
}

bool PlayerInput::Deny()
{
    return false;
}

bool PlayerInput::Up()
{
    return false;
}

bool PlayerInput::Down()
{
    return false;
}

bool PlayerInput::Attack()
{
    return false;
}

bool PlayerInput::Dodge()
{
    return false;
}

Vector2 PlayerInput::Camera()
{
    return InputSystem::GetRightStick();
}

Vector2 PlayerInput::Move()
{
    return Vector2();
}
