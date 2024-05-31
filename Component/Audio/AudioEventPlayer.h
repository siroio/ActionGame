#pragma once
#include <Component.h>

namespace Glib
{
    class AudioSource;
    class EventMsg;
}

/**
 * @brief イベント音声再生用コンポーネント
 */
class AudioEventPlayer : public Component
{
public:
    AudioEventPlayer(unsigned int msgID);
    void Start();
    void ReceiveEvent(const Glib::EventMsg& msg);

private:
    Glib::WeakPtr<Glib::AudioSource> audioSource_{};
    int msgID_{ -1 };
};
