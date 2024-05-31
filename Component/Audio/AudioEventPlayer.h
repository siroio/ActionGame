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
    AudioEventPlayer(unsigned int clipID, unsigned int msgID);
    void Start();
    void ReceiveMsg(const Glib::EventMsg& msg);

private:
    Glib::WeakPtr<Glib::AudioSource> audioSource_{};
    int clipID_{ -1 };
    int msgID_{ -1 };
};
