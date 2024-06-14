#include "AudioEventPlayer.h"
#include <Components/AudioSource.h>
#include <GameObject.h>
#include <EventMsg.h>
#include <Debugger.h>

using namespace Glib;

AudioEventPlayer::AudioEventPlayer(unsigned int clipID, unsigned int msgID) :
    clipID_{ static_cast<int>(clipID) }, msgID_{ static_cast<int>(msgID) }
{}

void AudioEventPlayer::Start()
{
    // 無効なIDの場合はコンポーネントを削除
    if (clipID_ < 0 || msgID_ < 0)
    {
        Debug::Log("Invalid ID.");
        Destroy(); // コンポーネントを削除
        return;
    }
    audioSource_ = GameObject()->GetComponent<AudioSource>();
}

void AudioEventPlayer::ReceiveMsg(const EventMsg& msg)
{
    if (msg.MsgID() != msgID_) return;
    audioSource_->AudioID(clipID_);
    audioSource_->Play();
}
