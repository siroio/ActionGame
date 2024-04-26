#pragma once
#include <GameObjectPtr.h>

struct Vector3;

struct Skeleton
{
    static GameObjectPtr Spawn(const Vector3& position, const Vector3& euler, const Vector3& scale);
};
