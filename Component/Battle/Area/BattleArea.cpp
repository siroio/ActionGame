#include "BattleArea.h"
#include <Components/SphereCollider.h>
#include <GameObject.h>
#include <EventMsg.h>
#include <Debugger.h>

#include "../../../Enum/MessageID.h"
#include "../../Audio/BGMController.h"
#include "../Wave/Wave.h"
#include "../../../Enum/AudioID.h"

using namespace Glib;

void BattleArea::Start()
{
    collider_ = GameObject()->GetComponent<SphereCollider>();
    bgmController = GameObjectManager::Find("BGMController")->GetComponent<BGMController>();
}

void BattleArea::AddtWave(const WavePtr& wave)
{
    wave->GameObject()->Active(false);
    waves_.push_back(wave);
}

void BattleArea::SetNextWave()
{
    if (waves_.size() <= 0) return;
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
            SetNextWave();
            StartWave();
            break;
        case MessageID::BattleClear:
            EndBattle();
            break;
    }
}

void BattleArea::StartBattle()
{
    Debug::Log("=== BattleStart ===");

    // 連続して開始が呼ばれないようにオフにする
    collider_->Active(false);

    SetNextWave(); // ウェーブを設定

    // ウェーブが設定されてない場合は開始しない
    if (currentWave_.expired())
    {
        Debug::Log("BattleStart failed. \nInvalid Wave.");
        return;
    }

    GameObject()->SendMsg(MessageID::BattleStart, nullptr);
    bgmController->Change(AudioID::Battle);
    StartWave();
}

void BattleArea::StartWave()
{
    if (currentWave_.expired()) return;
    currentWave_->GameObject()->Active(true);
    currentWave_->WaveStart();
}

void BattleArea::EndBattle()
{
    Debug::Log("=== BattleEnd ===");
    bgmController->Change(AudioID::Field);
    GameObject()->Destroy();
}
