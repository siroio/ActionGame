#include "TitleScene.h"
#include <Components/Canvas.h>
#include <Components/Camera.h>
#include <SceneManager.h>
#include <GameObjectManager.h>
#include <GameObject.h>

#include "../Character/UI/TitleMenu/TitleMenu.h"
#include "../Component/Player/PlayerInput.h"
#include "../Constant/SceneName.h"

using namespace Glib;

void TitleScene::Start()
{
    auto dummy = GameObjectManager::Instantiate("Player");
    dummy->AddComponent<Camera>();
    dummy->AddComponent<PlayerInput>();
    auto titleCanvas = GameObjectManager::Instantiate("TitleCanvas");
    titleCanvas->AddComponent<Canvas>();
    TitleMenu::Create(titleCanvas);
    // Glib::SceneManager::LoadScene(SceneName::PLAY);
}

void TitleScene::End()
{}
