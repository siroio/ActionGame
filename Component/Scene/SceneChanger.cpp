#include "SceneChanger.h"
#include <GameObject.h>
#include <SceneManager.h>

#include "../Fade/UIFader.h"

using namespace Glib;

namespace
{
    // シーン推移の初期時間
    constexpr float DEFAULT_DURATION{ 2.0f };
}

SceneChanger::SceneChanger(const Glib::WeakPtr<UIFader>& fader) :
    fader_{ fader }
{}

void SceneChanger::Update()
{
    if (!isChange_ || !fader_->IsEndFade()) return;
    SceneManager::LoadScene(nextScene_);
    isChange_ = false;
}

void SceneChanger::Change(std::string_view scene, float duration)
{
    if (scene.empty() || fader_.expired()) return;
    fader_->StartFade(duration);
    fader_->SetEndAlpha(1.0f);
    nextScene_ = scene;
    isChange_ = true;
}

void SceneChanger::Change(std::string_view scene)
{
    Change(scene, DEFAULT_DURATION);
}
