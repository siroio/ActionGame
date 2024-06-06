#include "SceneChangeButton.h"
#include <SceneManager.h>

#include "../Scene/SceneChanger.h"

using namespace Glib;

SceneChangeButton::SceneChangeButton(std::string_view sceneName, const Glib::WeakPtr<SceneChanger>& sceneChanger) :
    sceneName_{ sceneName }, sceneChanger_{ sceneChanger }
{}

SceneChangeButton::SceneChangeButton(std::string_view sceneName) :
    sceneName_{ sceneName }
{}

void SceneChangeButton::Comfirm()
{
    if (sceneChanger_.expired())
    {
        SceneManager::LoadScene(sceneName_);
    }
    else
    {
        sceneChanger_->Change(sceneName_);
    }
}
