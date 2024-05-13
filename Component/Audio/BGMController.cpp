#include "BGMController.h"
#include <Components/AudioSource.h>
#include <GameObject.h>
#include <GLGUI.h>

#include "../Fade/AudioFader.h"
#include "../../Enum/MessageID.h"

using namespace Glib;

void BGMController::Start()
{
    audioSource_ = GameObject()->GetComponent<AudioSource>();
    fader_ = GameObject()->GetComponent<AudioFader>();
    fader_->SetEase(Ease::OutQuart);
}

void BGMController::Update()
{
    // フェードアウト中に次のBGMへ推移しないようにブロック
    if (!(onChange_ && fader_->IsEndFade())) return;
    audioSource_->AudioID(nextBGMID_);
    audioSource_->Play();
    fader_->SetVolume(1.0f);
    fader_->StartFade(fadeDuration_);
    nextBGMID_ = -1;
    onChange_ = false;
}

void BGMController::Change(unsigned int id)
{
    // 現在のBGMをフェードアウト
    nextBGMID_ = id;
    onChange_ = true;
    fader_->SetVolume(0.0f);
    fader_->StartFade(fadeDuration_);
}

void BGMController::OnGUI()
{
    GLGUI::DragFloat("FadeDuration", &fadeDuration_, 0.01f, 0.0f, 10.0f);
    GLGUI::InputInt("NextBGM", &nextBGMID_);
}
