#include "AudioEventPlayer.h"
#include <Components/AudioSource.h>
#include <GameObject.h>
#include <EventMsg.h>

using namespace Glib;

AudioEventPlayer::AudioEventPlayer(unsigned int msgID) :
    msgID_{ static_cast<int>(msgID) }
{}

void AudioEventPlayer::Start()
{
    audioSource_ = GameObject()->GetComponent<AudioSource>();
}

void AudioEventPlayer::ReceiveEvent(const EventMsg& msg)
{
    if (msg.MsgID() != msgID_) return;
    if (msg.ValidateType<unsigned int>())
    {
        audioSource_->AudioID(msg.Msg<unsigned int>());
    }
    audioSource_->Play();
}
