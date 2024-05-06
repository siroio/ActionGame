#pragma once
#include <Component.h>

namespace Glib
{
    class AudioSource;
}

class ElapsedTimer;

class DelayedAudioPlayer : public Component
{
public:
    void Start();
    void Update();

    /**
     * @brief 指定秒後に再生
     * @param delay
     */
    void Play(float delay);

    /**
     * @brief 停止
     */
    void Stop();

private:
    Glib::WeakPtr<Glib::AudioSource> audioSource_{};
    Glib::WeakPtr<ElapsedTimer> elapsedTimer_{};
    float delayTime_{ 0.0f };
};
