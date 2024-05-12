#pragma once
#include <Component.h>

/**
 * @brief タイマークラス
 * @brief コンポーネントがアクティブな時間を計測
 */
class ElapsedTimer : public Component
{
public:
    enum class Mode
    {
        Scaled,
        UnScaled,
    };

public:
    ElapsedTimer(const Mode& mode = Mode::Scaled);
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
    Mode mode_{ Mode::Scaled };
    float elapsedTime_{ 0.0f };
};
