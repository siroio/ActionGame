#include "LastBattleArea.h"
#include <GameObject.h>
#include <GameObjectManager.h>
#include <EventMsg.h>

#include "BattleArea.h"
#include "../../Event/GameResultController.h"
#include "../../../Enum/MessageID.h"
#include "../../../Enum/AudioID.h"

using namespace Glib;

void LastBattleArea::Start()
{
    battleArea_ = GameObject()->GetComponent<BattleArea>();
    auto result = GameObjectManager::Find("GameResult");
    if (result.expired()) return;
    resultEventer_ = result->GetComponent<GameResultController>();
}

void LastBattleArea::ReceiveMsg(const Glib::EventMsg& msg)
{
    if (msg.MsgID() != MessageID::BattleClear) return;
    if (resultEventer_.expired()) return;
    GameObject()->SendMsg(MessageID::GameClear, nullptr, resultEventer_->GameObject());
}
