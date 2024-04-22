#pragma once
#include <GameObjectPtr.h>
#include <Vector3.h>

struct MainCamera
{
    static GameObjectPtr Spawn(const Vector3& offset, const float distance);
};
