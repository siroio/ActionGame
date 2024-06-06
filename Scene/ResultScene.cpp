#include "ResultScene.h"
#include <Components/Camera.h>
#include <GameObject.h>
#include <GameObjectManager.h>
#include <SkyboxManager.h>
#include "../Character/UI/ScreenFader/ScreenFader.h"
#include "../Component/Player/PlayerInput.h"
#include "../Constant/SceneName.h"

using namespace Glib;

void ResultScene::Start()
{
    SkyboxManager::SetSkybox(0);
    auto player = GameObjectManager::Instantiate("Player");
    auto camera = player->AddComponent<Camera>();
    camera->ClearFlags(CameraClearFlags::SkyBox);
    player->AddComponent<PlayerInput>();


}

void ResultScene::End()
{

}
