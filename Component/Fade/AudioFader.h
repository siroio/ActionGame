#pragma once
#include <Component.h>
#include <functional>

namespace Glib
{
    class AudioSource;
}

class ElapsedTimer;

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
};
