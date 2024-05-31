#include "SceneChangeButton.h"
#include <SceneManager.h>

using namespace Glib;

SceneChangeButton::SceneChangeButton(std::string_view sceneName) :
    sceneName_{ sceneName }
{}

void SceneChangeButton::Comfirm()
{
    SceneManager::LoadScene(sceneName_);
}
