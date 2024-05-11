#include "BattleArea.h"
#include <Components/SphereCollider.h>
#include <GameObject.h>
#include <EventMsg.h>
#include <Debugger.h>

#include "../../../Enum/MessageID.h"
#include "../Wave/Wave.h"

using namespace Glib;

void BattleArea::Start()
{
    collider_ = GameObject()->GetComponent<SphereCollider>();
    collider_->Radius(range_);
    collider_->IsTrigger(true);
    collider_->IsVisible(true); // デバッグのみ表示
}

void BattleArea::AddtWave(const WavePtr& wave)
{
    waves_.push_back(wave);
}

void BattleArea::StartNextWave()
{
    currentWave_ = waves_.front();
    waves_.pop_front();
}

bool BattleArea::HasNextWave() const
{
    return !waves_.empty();
}

void BattleArea::OnTriggerEnter(const GameObjectPtr& other)
{
    // 戦闘開始
    StartBattle();
}

void BattleArea::ReceiveMsg(const Glib::EventMsg& msg)
{
    switch (msg.MsgID())
    {
        case MessageID::WaveClear:
            StartNextWave();
            return;
        case MessageID::BattleClear:
            EndBattle();
            return;
    }
}

void BattleArea::StartBattle()
{
    Debug::Log("=== BattleStart ===");

    StartNextWave(); // ウェーブを開始

    if (currentWave_.expired())
    {
        Debug::Log("BattleStart failed. \nInvalid Wave.");
        return;
    }

    GameObject()->SendMsg(MessageID::BattleStart, nullptr);
    currentWave_->WaveStart();
}

void BattleArea::EndBattle()
{
    Debug::Log("=== BattleEnd ===");
    GameObject()->Destroy();
}
