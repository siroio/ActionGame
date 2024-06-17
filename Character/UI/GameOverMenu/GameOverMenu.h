#pragma once
#include <GameObjectPtr.h>

class SceneChanger;

struct GameOverMenu
{
    static GameObjectPtr Create(const GameObjectPtr& canvas, const Glib::WeakPtr<SceneChanger>& sceneChanger);
};
