#pragma once
#include <GameObjectPtr.h>

struct Vector3;
class MenuItem;

struct TitleMenu
{
    static void Create(const GameObjectPtr& canvas);

private:
    static Glib::WeakPtr<MenuItem> SetupMenuMenuButton(
        const GameObjectPtr& item,
        const Vector3& position,
        const Vector3& euler,
        const Vector3& scale,
        unsigned int textureID);
};
