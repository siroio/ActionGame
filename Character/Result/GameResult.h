#pragma once
#include <GameObjectPtr.h>

class GameResultController;

struct GameResult
{
    static Glib::WeakPtr<GameResultController> Spawn();
};
