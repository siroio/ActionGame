#pragma once
#include <Component.h>
#include "../../Enum/TimeScale.h"

/**
 * @brief タイマークラス
 * @brief コンポーネントがアクティブな時間を計測
 */
class ElapsedTimer : public Component
{
public:
    ElapsedTimer(const TimerScale& mode = TimerScale::Scaled);
    void Update();

    /**
     * @brief タイマーをリセット
     */
    void Reset();

    /**
     * @brief 経過時間の取得
     * @return 秒
     */
    float Elapsed() const;

private:
    void OnGUI() override;

private:
    TimerScale mode_{ TimerScale::Scaled };
    float elapsedTime_{ 0.0f };
};
