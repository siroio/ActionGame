#include "GameResult.h"
#include <GameObject.h>
#include <GameObjectManager.h>

#include "../../Component/Event/GameResultEventer.h"

using namespace Glib;

Glib::WeakPtr<GameResultEventer> GameResult::Spawn()
{
    auto gameResult = GameObjectManager::Instantiate("GameResult");
    auto eventer = gameResult->AddComponent<GameResultEventer>();

    return eventer;
}
