#include "ResultScene.h"
#include <SceneManager.h>
#include "../Constant/SceneName.h"

void ResultScene::Start()
{
    Glib::SceneManager::LoadScene(SceneName::TITLE);
}

void ResultScene::End()
{}
