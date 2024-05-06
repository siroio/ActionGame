#pragma once
#include <GameObjectPtr.h>
struct Vector3;

struct MagicArrow
{
    static void Spawn(const Vector3& position, float speed, const GameObjectPtr& target);
};
