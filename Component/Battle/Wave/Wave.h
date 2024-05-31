#pragma once
#include <Component.h>

class BattleArea;

/**
 * @brief ウェーブコンポーネント
 */
class Wave : public Component
{
public:
    Wave(float duration);
    void Start();
    void Update();

    /**
     * @brief ウェーブを開始
     */
    void WaveStart();

    /**
     * @brief ウェーブが終わったか確認
     */
    bool IsWaveEnd() const;

private:
    float duration_{ 0.0f };
    float elapsedTime_{ 0.0f };
    Glib::WeakPtr<BattleArea> battleArea_{};
};
