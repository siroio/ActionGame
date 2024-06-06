#pragma once
#include <GameObjectPtr.h>

class GameResultEventer;

struct GameResult
{
    static Glib::WeakPtr<GameResultEventer> Spawn();
};
