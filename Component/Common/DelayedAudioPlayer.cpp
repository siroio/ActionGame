#include "DelayedAudioPlayer.h"
#include <Components/AudioSource.h>
#include <GameObject.h>

#include "ElapsedTimer.h"

void DelayedAudioPlayer::Start()
{
    audioSource_ = GameObject()->GetComponent<Glib::AudioSource>();
    elapsedTimer_ = GameObject()->GetComponent<ElapsedTimer>();
    elapsedTimer_->Active(delayTime_ >= 0.0f);
}

void DelayedAudioPlayer::Update()
{
    if (elapsedTimer_->Active()) return;
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
    // 再生と計測を停止
    audioSource_->Stop();
    elapsedTimer_->Active(false);
}
