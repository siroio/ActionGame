#pragma once
#include <Component.h>

namespace Glib
{
    class AudioSource;
    class EventMsg;
}

class ElapsedTimer;

/**
 * @brief 遅延音声再生コンポーネント
 */
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

    /**
     * @brief 再生するAudioClipのIDを設定
     * @param id
     */
    void SetClip(unsigned int id);

    /**
     * @brief 再生するAudioClipのピッチを設定
     * @param id
     */
    void SetPitch(float pitch);

private:
    Glib::WeakPtr<Glib::AudioSource> audioSource_{};
    Glib::WeakPtr<ElapsedTimer> elapsedTimer_{};
    float delayTime_{ 0.0f };
};
