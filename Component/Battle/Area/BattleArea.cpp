#include "BattleArea.h"
#include <Components/SphereCollider.h>
#include <GameObject.h>
#include <EventMsg.h>

#include "../../../Enum/MessageID.h"
#include "../Wave/Wave.h"
#include <Debugger.h>

using namespace Glib;

void BattleArea::Start()
{
    collider_ = GameObject()->GetComponent<SphereCollider>();
    collider_->Radius(range_);
    collider_->IsTrigger(true);
    collider_->IsVisible(true); // デバッグのみ表示
}

void BattleArea::SetStartWave(const Glib::WeakPtr<Wave>& wave)
{
    startWave_ = wave;
}

void BattleArea::OnTriggerEnter(const GameObjectPtr& other)
{
    // 戦闘開始
    StartBattle();
}

void BattleArea::ReceiveEvent(const Glib::EventMsg& msg)
{
    if (msg.MsgID() != MessageID::BattleClear) return;
    // 戦闘終了
    EndBattle();
}

void BattleArea::StartBattle()
{
    Debug::Log("=== BattleStart ===");
    if (startWave_.expired())
    {
        Debug::Log("BattleStart failed. \nInvalid Wave.");
        return;
    }
    GameObject()->SendMsg(MessageID::BattleStart, nullptr);
    startWave_->WaveStart();
}

void BattleArea::EndBattle()
{
    Debug::Log("=== BattleEnd ===");
    GameObject()->Destroy();
}
