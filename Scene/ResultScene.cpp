#include "ResultScene.h"
#include <Components/Camera.h>
#include <Components/Canvas.h>
#include <Components/Image.h>
#include <Components/AudioSource.h>
#include <Components/Animator.h>
#include <Components/MeshRenderer.h>
#include <Components/SkinnedMeshRenderer.h>
#include <Components/DirectionalLight.h>
#include <GameObject.h>
#include <GameObjectManager.h>
#include <SkyboxManager.h>

#include "../Character/UI/ResultMenu/ResultMenu.h"
#include "../Character/UI/ScreenFader/ScreenFader.h"
#include "../Component/Common/ElapsedTimer.h"
#include "../Component/Player/PlayerInput.h"
#include "../Component/Player/State/PlayerIdleState.h"
#include "../Component/Audio/AudioEventPlayer.h"
#include "../Component/Audio/BGMController.h"
#include "../Component/Fade/AudioFader.h"
#include "../Component/Fade/UIFader.h"
#include "../Component/Scene/SceneChanger.h"
#include "../Component/StateMachine/StateBehavior.h"
#include "../Component/StateMachine/AnimationInfo.h"
#include "../Constant/SceneName.h"
#include "../Enum/State/PlayerState.h"
#include "../Enum/AudioGroupID.h"
#include "../Enum/AudioID.h"
#include "../Enum/MessageID.h"
#include "../Enum/MeshID.h"
#include "../Enum/AnimationID.h"
#include "../Enum/TextureID.h"

using namespace Glib;

namespace
{
    const Vector3 STAGE_POSITION{ -40.0f, 0.0f, -44.0f };
    const Vector3 STAGE_EULER{ 0.0f, 90.0f, 0.0f };

    const Vector3 LIGHT_EULER{ 40.0f, 280.0f, 0.0f };

    const Vector3 CAMERA_POSITION{ 3.0f, 1.0f, 7.5f };
    const Vector3 CAMERA_EULER{ 340.0f, 0.0f, 0.0f };

    const Vector3 WARRIOR_POSITION{ 4.0f, 0.0f, 9.5f };
    const Vector3 WARRIOR_EULER{ 0.0f, 220.0f, 0.0f };

    const Color BG_COLOR{ 0.0f, 0.0f, 0.0f, 0.5 };
    const Vector3 TEXT_POSITION{ 960.0f, 440.0f, 0.0f };
}

void ResultScene::Start()
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

    auto warrior = GameObjectManager::Instantiate("Warrior");
    warrior->AddComponent<SkinnedMeshRenderer>()->MeshID(MeshID::Player);
    auto animator = warrior->AddComponent<Animator>();
    warrior->Transform()->Position(WARRIOR_POSITION);
    warrior->Transform()->EulerAngles(WARRIOR_EULER);

    auto idle = warrior->AddComponent<PlayerIdleState>(PlayerState::SwordRaise, 3.0f);
    idle->SetAnimationInfo(AnimationInfo{ AnimationID::PlayerIdle, 0.0f, 0.1f, 1.0f, true });

    auto raise = warrior->AddComponent<PlayerIdleState>(PlayerState::Idle, 0.75f);
    raise->SetAnimationInfo(AnimationInfo{ AnimationID::PlayerUpArm, 0.0f, 0.1f, 1.0f, true });

    auto stateBehavior = warrior->AddComponent<StateBehavior>();
    stateBehavior->AddState(idle, PlayerState::Idle);
    stateBehavior->AddState(raise, PlayerState::SwordRaise);

    auto bgmController = GameObjectManager::Instantiate("BGMController");
    auto bgmSource = bgmController->AddComponent<AudioSource>();
    bgmSource->SetGroup(AudioGroupID::BGM);
    bgmSource->AudioID(AudioID::GameClear);
    bgmSource->PlayOnStart(true);
    bgmSource->Loop(true);
    bgmSource->Volume(0.0f);
    auto controller = bgmController->AddComponent<BGMController>();
    auto bgmFader = bgmController->AddComponent<AudioFader>();
    bgmFader->SetVolume(1.0f);
    bgmFader->StartFade(2.0f);
    bgmController->AddComponent<ElapsedTimer>();

    auto fader = ScreenFader::Create(2.0f, true, 0.0f, Color::White(), TimerScale::Scaled);
    auto sceneChanger = GameObjectManager::Instantiate("SceneChanger")
        ->AddComponent<SceneChanger>(fader);

    auto resultCanvas = GameObjectManager::Instantiate("ResultCanvas");
    resultCanvas->AddComponent<Canvas>();

    auto bgObj = GameObjectManager::Instantiate("GameClearBG");
    auto bgImg = bgObj->AddComponent<Image>();
    bgImg->TextureID(TextureID::Fade);
    bgImg->Center(Vector2::Zero());
    bgImg->Color(BG_COLOR);
    bgObj->Transform()->Parent(resultCanvas->Transform());

    auto menu = ResultMenu::Create(resultCanvas, sceneChanger);
    menu->AddComponent<AudioSource>()->SetGroup(AudioGroupID::SE);
    menu->AddComponent<AudioEventPlayer>(AudioID::ButtonPush, MessageID::Comfirm);
    menu->AddComponent<AudioEventPlayer>(AudioID::CursorMove, MessageID::CursorMove);

    auto textObj = GameObjectManager::Instantiate("GameClearText");
    auto textImg = textObj->AddComponent<Image>();
    textImg->TextureID(TextureID::GameClear);
    textObj->Transform()->Position(TEXT_POSITION);
    textObj->Transform()->Parent(resultCanvas->Transform());

    auto stage = GameObjectManager::Instantiate("ResultStage");
    stage->AddComponent<MeshRenderer>()->MeshID(MeshID::WALL_3);
    stage->AddComponent<MeshRenderer>()->MeshID(MeshID::WALL_4);
    stage->AddComponent<MeshRenderer>()->MeshID(MeshID::WALL_5);
    stage->AddComponent<MeshRenderer>()->MeshID(MeshID::Mountain);
    stage->AddComponent<MeshRenderer>()->MeshID(MeshID::Ground);
    stage->Transform()->Position(STAGE_POSITION);
    stage->Transform()->EulerAngles(STAGE_EULER);
}

void ResultScene::End()
{

}
