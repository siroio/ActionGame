#include "TitleScene.h"
#include <Components/Canvas.h>
#include <Components/Camera.h>
#include <Components/AudioSource.h>
#include <Components/MeshRenderer.h>
#include <Components/DirectionalLight.h>
#include <SceneManager.h>
#include <SkyboxManager.h>
#include <GameObjectManager.h>
#include <GameObject.h>

#include "../Character/UI/TitleMenu/TitleMenu.h"
#include "../Character/UI/ScreenFader/ScreenFader.h"
#include "../Component/Common/ElapsedTimer.h"
#include "../Component/Player/PlayerInput.h"
#include "../Component/Audio/AudioEventPlayer.h"
#include "../Component/Audio/BGMController.h"
#include "../Component/Fade/AudioFader.h"
#include "../Component/Fade/UIFader.h"
#include "../Component/Scene/SceneChanger.h"
#include "../Constant/SceneName.h"
#include "../Enum/AudioGroupID.h"
#include "../Enum/AudioID.h"
#include "../Enum/MessageID.h"
#include "../Enum/MeshID.h"

using namespace Glib;

namespace
{
    const Vector3 LIGHT_EULER{ 22.0f, 200.0f, 0.0f };
    const Vector3 CAMERA_POSITION{ -6.73f, 1.50f, 24.36f };
    const Vector3 CAMERA_EULER{ 0.0f, 180.0f, 0.0f };
}

void TitleScene::Start()
{
    SkyboxManager::SetSkybox(0);
    auto lightObj = GameObjectManager::Instantiate("DirectionalLight");;
    lightObj->AddComponent<DirectionalLight>();
    lightObj->Transform()->EulerAngles(LIGHT_EULER);

    auto player = GameObjectManager::Instantiate("Player");
    auto camera = player->AddComponent<Camera>();
    camera->ClearFlags(CameraClearFlags::SkyBox);
    player->AddComponent<PlayerInput>();
    player->Transform()->Position(CAMERA_POSITION);
    player->Transform()->EulerAngles(CAMERA_EULER);

    auto fader = ScreenFader::Create(1.5f, true, TimerScale::Scaled);
    auto sceneChanger = GameObjectManager::Instantiate("SceneChanger")
        ->AddComponent<SceneChanger>(fader);

    auto bgmController = GameObjectManager::Instantiate("BGMController");
    auto bgmSource = bgmController->AddComponent<AudioSource>();
    bgmSource->SetGroup(AudioGroupID::BGM);
    bgmSource->AudioID(AudioID::Title);
    bgmSource->PlayOnStart(true);
    bgmSource->Loop(true);
    bgmSource->Volume(0.0f);
    auto controller = bgmController->AddComponent<BGMController>();
    auto bgmFader = bgmController->AddComponent<AudioFader>();
    bgmFader->SetVolume(1.0f);
    bgmFader->StartFade(2.0f);
    bgmController->AddComponent<ElapsedTimer>();

    auto titleCanvas = GameObjectManager::Instantiate("TitleCanvas");
    titleCanvas->AddComponent<Canvas>();
    auto menu = TitleMenu::Create(titleCanvas, sceneChanger);
    menu->AddComponent<AudioSource>()->SetGroup(AudioGroupID::SE);
    menu->AddComponent<AudioEventPlayer>(AudioID::ButtonPush, MessageID::Comfirm);
    menu->AddComponent<AudioEventPlayer>(AudioID::CursorMove, MessageID::CursorMove);

    auto mesh = GameObjectManager::Instantiate("TitleStage");
    mesh->AddComponent<MeshRenderer>()->MeshID(MeshID::TitleStage);
}

void TitleScene::End()
{}
