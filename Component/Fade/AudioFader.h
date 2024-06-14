#pragma once
#include <Component.h>
#include <functional>
#include <Easing.h>

namespace Glib
{
    class AudioSource;
}

class ElapsedTimer;

/**
 * @brief 音声フェードコンポーネント
 */
class AudioFader : public Component
{
public:
    void Start();
    void Update();
    void StartFade(float duration);
    bool IsEndFade();

    /**
     * @brief 終了時の音量を設定
     * @param endVolume
     */
    void SetVolume(float endVolume);

    /**
     * @brief 補完方法を設定
     * @param type
     */
    void SetEase(Ease type);

private:
    void UpdateFade();
    bool InvalidFader();

private:
    Glib::WeakPtr<Glib::AudioSource> audioSource_{};
    Glib::WeakPtr<ElapsedTimer> elapsedTimer_{};
    float duration_{ 0.0f };
    float startVolume_{ 0.0f };
    float endVolume_{ 0.0f };
    bool isFade_{ false };
    Ease easeType_{ Ease::Linear };
};
