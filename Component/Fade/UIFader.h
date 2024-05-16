#pragma once
#include <Component.h>
#include <Easing.h>

namespace Glib
{
    class Image;
}

class ElapsedTimer;

class UIFader : public Component
{
public:
    void Start();
    void Update();
    void StartFade(float duration);
    bool IsEndFade();

    /**
     * @brief 終了時の音量を設定
     * @param endAlpha
     */
    void SetEndAlpha(float endAlpha);

    /**
     * @brief イージングの種類を設定
     * @param ease
     */
    void SetEase(Ease ease);

private:
    void UpdateFade();
    bool InvalidFader();

private:
    Glib::WeakPtr<Glib::Image> image_{};
    Glib::WeakPtr<ElapsedTimer> elapsedTimer_{};
    float duration_{ 0.0f };
    float startAlpha_{ 1.0f };
    float endAlpha_{ 0.0f };
    bool isCrossFade_{ false };
    Ease easeType_{ Ease::Linear };
};
