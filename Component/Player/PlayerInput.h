#pragma once
#include <Component.h>

struct Vector2;

class PlayerInput : public Component
{
public:
    bool Pose();
    bool Comfirm();
    bool Deny();
    bool Up();
    bool Down();
    bool Attack();
    bool Dodge();
    Vector2 Camera();
    Vector2 Move();
};
