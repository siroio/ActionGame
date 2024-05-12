#include "AudioFader.h"
#include <Components/AudioSource.h>
#include <GameObject.h>
#include <GameTimer.h>
#include <Mathf.h>

#include "../Common/ElapsedTimer.h"
#include "../../Constant/GameObjectName.h"

using namespace Glib;

void AudioFader::Start()
{
    audioSource_ = GameObject()->GetComponent<AudioSource>();
    elapsedTimer_ = GameObject()->GetComponent<ElapsedTimer>();
}

void AudioFader::Update()
{
    if (InvalidFader() || !isFade_) return;
    UpdateFade();
}

void AudioFader::StartFade(float duration)
{
    isFade_ = true;
    duration_ = duration;
    if (!elapsedTimer_.expired())
    {
        elapsedTimer_->Reset();
    }
    if (!audioSource_.expired())
    {
        startVolume_ = audioSource_->Volume();
    }
}

bool AudioFader::IsEndFade()
{
    return elapsedTimer_->Elapsed() >= duration_;
}

void AudioFader::SetVolume(float endVolume)
{
    endVolume_ = endVolume;
}

void AudioFader::UpdateFade()
{
    float t = Mathf::Min(elapsedTimer_->Elapsed() / duration_, 1.0f);
    float volume = Mathf::Lerp(startVolume_, endVolume_, t);
    audioSource_->Volume(volume);
    if (t >= 1.0f) isFade_ = false;
}

bool AudioFader::InvalidFader()
{
    return elapsedTimer_.expired() || audioSource_.expired();
}
