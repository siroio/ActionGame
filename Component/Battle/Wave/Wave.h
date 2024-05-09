#pragma once
#include <Component.h>

class ElapsedTimer;

class Wave : public Component
{
public:
    Wave(float duration);
    void Start();
    void Update();

    /**
     * @brief 次のウェーブを設定
     * @param wave
     */
    void SetNextWave(const Glib::WeakPtr<Wave>& wave);

    /**
     * @brief 次のウェーブがあるかチェック
     * @return
     */
    bool HasNextWave() const;

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
    Glib::WeakPtr<ElapsedTimer> timer_{};
    Glib::WeakPtr<Wave> nextWave_{};
};
