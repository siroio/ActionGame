#pragma once
#include <GameObjectPtr.h>

struct Vector3;
struct Color;

struct Light
{
    static GameObjectPtr Spawn(const Vector3& euler, const Color& ambient, const Color& diffuse, const Color& specular);
};
