#include "GameResult.h"
#include <GameObject.h>
#include <GameObjectManager.h>

#include "GameOver.h"
#include "GameClear.h"
#include "../../Component/Event/GameResultController.h"
#include "../../Component/Event/PlayerDeadObserver.h"
#include "../../Constant/GameObjectName.h"

using namespace Glib;

Glib::WeakPtr<GameResultController> GameResult::Spawn()
{
    auto gameResult = GameObjectManager::Instantiate("GameResult");
    auto player = GameObjectManager::Instantiate(ObjectName::Player);
    gameResult->AddComponent<PlayerDeadObserver>();
    auto eventer = gameResult->AddComponent<GameResultController>();

    eventer->AddObject(ResultType::GameOver, GameOver::Create());
    eventer->AddObject(ResultType::GameClear, GameClear::Create());

    return eventer;
}
