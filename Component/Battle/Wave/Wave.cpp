#include "Wave.h"
#include <GameObject.h>

#include "../../Common/ElapsedTimer.h"
#include "../../../Enum/MessageID.h"

Wave::Wave(float duration) :
    duration_{ duration }
{}

void Wave::Start()
{
    timer_ = GameObject()->GetComponent<ElapsedTimer>();
}

void Wave::Update()
{
    if (timer_->Elapsed() <= duration_) return;
    if (!IsWaveEnd()) return;

    if (HasNextWave())
    {
        nextWave_->GameObject()->Active(true);
    }
    else
    {
        const auto& battleArea = GameObject()->Transform()->Parent();
        GameObject()->SendMsg(MessageID::BattleClear, nullptr, battleArea->GameObject());
    }
}

void Wave::SetNextWave(const Glib::WeakPtr<Wave>& wave)
{
    nextWave_ = wave;
}

bool Wave::HasNextWave() const
{
    return !nextWave_.expired();
}

void Wave::WaveStart()
{
    timer_->Reset();
    timer_->Active(true);
}

bool Wave::IsWaveEnd() const
{
    // 子オブジェクト(敵)がいない場合終了と判断
    return GameObject()->Transform()->Children().empty();
}
