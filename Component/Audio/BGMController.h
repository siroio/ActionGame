#pragma once
#include <Component.h>

namespace Glib
{
    class AudioSource;
    class EventMsg;
}
class AudioFader;

/**
 * @brief BGM制御用コンポーネント
 */
class BGMController : public Component
{
public:
    void Start();
    void Update();
    void Change(unsigned int id);

private:
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::AudioSource> audioSource_{};
    Glib::WeakPtr<AudioFader> fader_{};
    float fadeDuration_{ 2.0f };
    bool onChange_{ false };
    int nextBGMID_{ -1 };
};
