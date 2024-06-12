#include "PlayScene.h"
#include <Components/AudioSource.h>
#include <Components/Canvas.h>
#include <Components/MeshRenderer.h>
#include <Components/MeshCollider.h>
#include <GameObject.h>
#include <GameObjectManager.h>
#include <SkyboxManager.h>
#include <Color.h>
#include <GameTimer.h>

#include "../Character/Light/Light.h"
#include "../Character/Camera/MainCamera.h"
#include "../Character/Player/Player.h"
#include "../Character/Enemy/Golem/Golem.h"
#include "../Character/Stage/Stage.h"
#include "../Character/Menu/SafeArea/SafeArea.h"
#include "../Character/UI/HPGauge/HPGauge.h"
#include "../Character/UI/Button/UIButton.h"
#include "../Component/Camera/CameraController.h"
#include "../Component/Audio/BGMController.h"
#include "../Component/Fade/AudioFader.h"
#include "../Component/Common/ElapsedTimer.h"
#include "../Character/UI/ScreenFader/ScreenFader.h"
#include "../Generator/BattleAreaGenerator.h"
#include "../Enum/AudioGroupID.h"
#include "../Enum/AudioID.h"
#include "../Enum/CollisionLayer.h"

using namespace Glib;

namespace
{
    const Vector3 LIGHT_DIRECTION{ 60.0f, 290.0f, 0.0f };
    const Color LIGHT_AMBIENT{ 0.7f, 0.7f, 0.7f, 1.0f };
    const Color LIGHT_DIFFUSE{ 0.7f, 0.7f, 0.7f, 1.0f };
    const Color LIGHT_SPECULAR{ 0.4f, 0.4f, 0.4f, 1.0f };
    constexpr unsigned int DEFAULT_SKYBOX{ 0 };
    const Vector3 MAIN_CAMERA_OFFSET{ 0.0f, 1.6f, 0.0f };
    constexpr float MAIN_CAMERA_DISTANCE{ 2.5f };
    constexpr char BATTLE_AREA[]{ "Assets/Area" };
}

void PlayScene::Start()
{
    // オブジェクト生成
    Light::Spawn(LIGHT_DIRECTION, LIGHT_AMBIENT, LIGHT_DIFFUSE, LIGHT_SPECULAR);
    SkyboxManager::SetSkybox(DEFAULT_SKYBOX);
    GameObjectPtr camera = MainCamera::Spawn(MAIN_CAMERA_OFFSET, MAIN_CAMERA_DISTANCE);
    GameObjectPtr player = Player::Spawn();

    // カメラのターゲットにプレイヤーを設定
    auto cameraController = camera->GetComponentInParent<CameraController>();
    cameraController->SetTarget(player->Transform());

    // UI生成
    auto uiCanvas = GameObjectManager::Instantiate("UICanvas");
    uiCanvas->AddComponent<Canvas>();
    HPGauge::Spawn(uiCanvas);
    UIButton::Spawn(uiCanvas);

    // 画面フェード
    ScreenFader::Create(1.5f, true, TimerScale::Scaled);

#ifdef _DEBUG
    // デバッグ時のみ
    SafeArea::Spawn(); // UI調整用
#endif

    auto bgmController = GameObjectManager::Instantiate("BGMController");
    auto bgmSource = bgmController->AddComponent<AudioSource>();
    bgmSource->SetGroup(AudioGroupID::BGM);
    bgmSource->AudioID(AudioID::Field);
    bgmSource->PlayOnStart(true);
    bgmSource->Loop(true);
    bgmSource->Volume(0.0f);
    auto controller = bgmController->AddComponent<BGMController>();
    auto fader = bgmController->AddComponent<AudioFader>();
    fader->SetVolume(1.0f);
    fader->StartFade(2.0f);
    bgmController->AddComponent<ElapsedTimer>();

    Stage::Spawn();
    Golem::Spawn(Vector3{ 0.0f, 0.0f, 4.0f }, Vector3::Zero(), Vector3::One());

    // 戦闘エリアと敵の生成
    // BattleAreaGenerator::Generate(BATTLE_AREA);
}

void PlayScene::End()
{
    GameTimer::TimeScale(1.0f);
}
