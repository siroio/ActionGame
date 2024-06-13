#pragma once
#include <GameObjectPtr.h>

class SceneChanger;

struct ResultMenu
{
    static GameObjectPtr Create(const GameObjectPtr& canvas, const Glib::WeakPtr<SceneChanger>& sceneChanger);
};
