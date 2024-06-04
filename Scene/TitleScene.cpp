#include "TitleScene.h"
#include <Components/Canvas.h>
#include <Components/Camera.h>
#include <Components/AudioSource.h>
#include <SceneManager.h>
#include <SkyboxManager.h>
#include <GameObjectManager.h>
#include <GameObject.h>

#include "../Character/UI/TitleMenu/TitleMenu.h"
#include "../Character/UI/ScreenFader/ScreenFader.h"
#include "../Component/Player/PlayerInput.h"
#include "../Component/Audio/AudioEventPlayer.h"
#include "../Component/Common/ElapsedTimer.h"
#include "../Component/Fade/UIFader.h"
#include "../Constant/SceneName.h"
#include "../Enum/AudioID.h"
#include "../Enum/MessageID.h"
#include "../Enum/AudioGroupID.h"


using namespace Glib;

void TitleScene::Start()
{
    SkyboxManager::SetSkybox(0);
    auto dummy = GameObjectManager::Instantiate("Player");
    auto camera = dummy->AddComponent<Camera>();
    camera->ClearFlags(CameraClearFlags::SkyBox);
    dummy->AddComponent<PlayerInput>();

    ScreenFader::Create(1.5f, true, TimerScale::Scaled);

    auto titleCanvas = GameObjectManager::Instantiate("TitleCanvas");
    titleCanvas->AddComponent<Canvas>();
    auto menu = TitleMenu::Create(titleCanvas);
    auto menuAudioSource = menu->AddComponent<AudioSource>();
    menuAudioSource->SetGroup(AudioGroupID::SE);
    menu->AddComponent<AudioEventPlayer>(AudioID::ButtonPush, MessageID::Comfirm);
    menu->AddComponent<AudioEventPlayer>(AudioID::CursorMove, MessageID::CursorMove);
}

void TitleScene::End()
{}
