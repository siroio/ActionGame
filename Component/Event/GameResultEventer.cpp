#include "GameResultEventer.h"
#include <GameObjectManager.h>
#include <GameObject.h>
#include <EventMsg.h>
#include <Debugger.h>

#include "../../Constant/ObjectTag.h"
#include "../../Enum/MessageID.h"

using namespace Glib;

void GameResultEventer::Start()
{
    gameClearObjects_ = GameObjectManager::FindGameObjectsWithTag(GameTag::GAMECLEAR);
    gameOverObjects_ = GameObjectManager::FindGameObjectsWithTag(GameTag::GAMEOVER);
}

void GameResultEventer::ReceiveEvent(const Glib::EventMsg& msg)
{
    switch (msg.MsgID())
    {
        case MessageID::GameClear:
            Debug::Log("=== GameClear ===");
            ActivateObjects(gameClearObjects_);
            return;
        case  MessageID::GameOver:
            Debug::Log("=== GameOver ===");
            ActivateObjects(gameOverObjects_);
            return;
    }
}

void GameResultEventer::ActivateObjects(const std::list<GameObjectPtr>& objects)
{
    for (const auto& object : objects)
    {
        if (object.expired()) continue;
        object->Active(true);
    }
}
