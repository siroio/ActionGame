#include "Wave.h"
#include <GameObject.h>
#include <GameTimer.h>

#include "../../../Enum/MessageID.h"
#include "../Area/BattleArea.h"


Wave::Wave(float duration) :
    duration_{ duration }
{}

void Wave::Start()
{
    battleArea_ = GameObject()->GetComponentInParent<BattleArea>();
}

void Wave::Update()
{
    if (elapsedTime_ <= duration_)
    {
        elapsedTime_ += Glib::GameTimer::DeltaTime();
        return;
    }
    if (!IsWaveEnd()) return;

    // 次のウェーブがある場合ウェーブクリアメッセージ
    // ない場合はバトルクリアを送信
    auto clearMsg = battleArea_->HasNextWave() ? MessageID::WaveClear : MessageID::BattleClear;

    // クリアのメッセージを送信
    const auto& battleArea = GameObject()->Transform()->Parent();
    GameObject()->SendMsg(clearMsg, nullptr, battleArea->GameObject());
    GameObject()->Destroy();
}

void Wave::WaveStart()
{
    elapsedTime_ = 0.0f;
}

bool Wave::IsWaveEnd() const
{
    // 子オブジェクト(敵)がいない場合終了と判断
    return GameObject()->Transform()->Children().empty();
}
