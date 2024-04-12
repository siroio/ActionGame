#include "Input.h"
#include <GearsInput/InputSystem.h>
#include <GearsInput/InputState.h>
#include <GearsMath/Mathf.h>
using namespace Glib;

Vector2 Input::Move()
{
    return InputSystem::GetLeftStick();
}

Vector2 Input::CameraRotate()
{
    return InputSystem::GetRightStick();
}

bool Input::CameraLook()
{
    return InputSystem::GetButtonDown(GPADKey::RIGHT_TRIGGER);
}

bool Input::Attack()
{
    return InputSystem::GetButtonDown(GPADKey::B);
}

bool Input::Dodge()
{
    return InputSystem::GetButtonDown(GPADKey::A);
}
