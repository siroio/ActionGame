#include "DelayedAudioPlayer.h"
#include <Components/AudioSource.h>
#include <GameObject.h>
#include <EventMsg.h>

#include "ElapsedTimer.h"

void DelayedAudioPlayer::Start()
{
    audioSource_ = GameObject()->GetComponent<Glib::AudioSource>();
    elapsedTimer_ = GameObject()->GetComponent<ElapsedTimer>();
    elapsedTimer_->Active(delayTime_ >= 0.0f);
}

void DelayedAudioPlayer::Update()
{
    if (!elapsedTimer_->Active()) return;
    if (elapsedTimer_->Elapsed() < delayTime_) return;

    audioSource_->Play();
    elapsedTimer_->Active(false);
}

void DelayedAudioPlayer::Play(float delay)
{
    // 時間を設定
    delayTime_ = delay;
    if (elapsedTimer_.expired()) return;
    elapsedTimer_->Reset();
    elapsedTimer_->Active(true);
}

void DelayedAudioPlayer::Stop()
{
    if (audioSource_.expired() || elapsedTimer_.expired()) return;
    // 再生を停止
    audioSource_->Stop();
    elapsedTimer_->Reset();
    elapsedTimer_->Active(true);
}

void DelayedAudioPlayer::SetClip(unsigned int id)
{
    if (audioSource_.expired()) return;
    audioSource_->AudioID(id);
}

void DelayedAudioPlayer::SetPitch(float pitch)
{
    if (audioSource_.expired()) return;
    audioSource_->Pitch(pitch);
}
