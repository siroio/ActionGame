#include "TitleScene.h"
#include <SceneManager.h>
#include "../Constant/SceneName.h"

void TitleScene::Start()
{
    Glib::SceneManager::LoadScene(SceneName::PLAY);
}

void TitleScene::End()
{}
