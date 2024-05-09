#include "BGMController.h"
#include <Components/AudioSource.h>
#include <GameObject.h>

#include "../Fade/AudioFader.h"

using namespace Glib;

namespace
{
    constexpr float BGM_FADE_DURATION{ 0.5f };
}

void BGMController::Start()
{
    audioSource_ = GameObject()->GetComponent<AudioSource>();
    fader_ = GameObject()->GetComponent<AudioFader>();
}

void BGMController::Update()
{

}

void BGMController::Change(unsigned int id)
{
    if (nextBGMID == id || id < 0) return;
    nextBGMID = id;
    audioSource_->Volume(0.0f);
    audioSource_->AudioID(id);
    fader_->SetVolume(1.0f);
    fader_->StartFade(BGM_FADE_DURATION);
}
