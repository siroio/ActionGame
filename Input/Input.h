#pragma once
#include <Vector2.h>

class Input
{
public:
    static Vector2 Move();
    static Vector2 CameraRotate();
    static bool CameraLook();
    static bool Attack();
    static bool Dodge();
};
