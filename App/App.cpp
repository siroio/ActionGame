#include "App.h"
#include "../Scene/TitleScene.h"
#include "../Scene/PlayScene.h"
#include "../Scene/ResultScene.h"
#include <GearsScene/SceneManager.h>

using namespace Glib;

void App::Start()
{
    ResiterScenes();
}

void App::End()
{}

void App::ResiterScenes()
{
    SceneManager::Register<TitleScene>();
    SceneManager::Register<PlayScene>();
    SceneManager::Register<ResultScene>();
}
