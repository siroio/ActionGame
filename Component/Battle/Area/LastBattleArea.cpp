#include "LastBattleArea.h"
#include <GameObject.h>
#include <EventMsg.h>
#include <Debugger.h>

#include "BattleArea.h"
#include "../../../Enum/MessageID.h"
#include "../../../Enum/AudioID.h"

using namespace Glib;

void LastBattleArea::Start()
{
    battleArea_ = GameObject()->GetComponent<BattleArea>();
}

void LastBattleArea::ReceiveMsg(const Glib::EventMsg& msg)
{
    if (msg.MsgID() == MessageID::BattleClear)
    {
        Debug::Log("=== GameClear ===");
        GameObject()->SendMsg(MessageID::GameClear, nullptr);
    }
}
