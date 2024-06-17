#include "GameResultController.h"
#include <GameObjectManager.h>
#include <GameObject.h>
#include <EventMsg.h>
#include <Debugger.h>

#include "../../Component/Audio/BGMController.h"
#include "../../Constant/ObjectTag.h"
#include "../../Enum/AudioID.h"
#include "../../Enum/MessageID.h"

using namespace Glib;

void GameResultController::Start()
{
    auto controller = GameObjectManager::Find("BGMController");
    bgmController_ = controller->GetComponent<BGMController>();
}

void GameResultController::ReceiveMsg(const EventMsg& msg)
{
    switch (msg.MsgID())
    {
        case MessageID::GameClear:
            Debug::Log("=== GameClear ===");
            ActivateObjects(gameClearObjects_);
            return;
        case  MessageID::Dead:
            Debug::Log("=== GameOver ===");
            ActivateObjects(gameOverObjects_);
            bgmController_->Change(AudioID::GameOver);
            return;
    }
}

void GameResultController::AddObject(ResultType type, const GameObjectPtr& gameObject)
{
    // updateなどが呼ばれないように無効にしておく
    gameObject->Active(false);
    switch (type)
    {
        using enum ResultType;
        case GameOver: gameOverObjects_.push_back(gameObject); break;
        case GameClear: gameClearObjects_.push_back(gameObject); break;
    }
}

void GameResultController::ActivateObjects(const std::list<GameObjectPtr>& objects)
{
    for (const auto& object : objects)
    {
        if (object.expired()) continue;
        object->Active(true);
    }
}
