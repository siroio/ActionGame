#include "Wave.h"
#include <GameObject.h>

#include "../../../Enum/MessageID.h"
#include "../../Common/ElapsedTimer.h"
#include "../Area/BattleArea.h"

Wave::Wave(float duration) :
    duration_{ duration }
{}

void Wave::Start()
{
    timer_ = GameObject()->GetComponent<ElapsedTimer>();
    battleArea_ = GameObject()->GetComponent<BattleArea>();
}

void Wave::Update()
{
    if (timer_->Elapsed() <= duration_) return;
    if (!IsWaveEnd()) return;

    // 次のウェーブがある場合ウェーブクリアメッセージ
    // ない場合はバトルクリアを送信
    auto clearMsg = battleArea_->HasNextWave() ? MessageID::WaveClear : MessageID::BattleClear;

    // クリアのメッセージを送信
    const auto& battleArea = GameObject()->Transform()->Parent();
    GameObject()->SendMsg(clearMsg, nullptr, battleArea->GameObject());
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
