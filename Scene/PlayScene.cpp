#include "PlayScene.h"
#include <Components/Canvas.h>
#include <Components/MeshRenderer.h>
#include <Components/MeshCollider.h>
#include <GameObject.h>
#include <GameObjectManager.h>
#include <SkyboxManager.h>
#include <Physics.h>
#include <Color.h>
#include <GameTimer.h>

#include "../Character/Light/Light.h"
#include "../Character/Camera/MainCamera.h"
#include "../Character/Player/Player.h"
#include "../Character/Enemy/Skeleton/Skeleton.h"
#include "../Character/Menu/SafeArea/SafeArea.h"
#include "../Character/UI/HPGauge/HPGauge.h"
#include "../Component/Camera/CameraController.h"
#include "../Enum/CollisionLayer.h"
#include "../Character/Projectile/MagicArrow.h"
#include "../Character/Enemy/Mage/Mage.h"


using namespace Glib;

namespace
{
    const Vector3 LIGHT_DIRECTION{ 70.0f, 0.0f, 0.0f };
    const Color LIGHT_AMBIENT{ 0.7f, 0.7f, 0.7f, 1.0f };
    const Color LIGHT_DIFFUSE{ 0.7f, 0.7f, 0.7f, 1.0f };
    const Color LIGHT_SPECULAR{ 0.4f, 0.4f, 0.4f, 1.0f };
    const unsigned int DEFAULT_SKYBOX{ 0 };
    const Vector3 MAIN_CAMERA_OFFSET{ 0.0f, 1.6f, 0.0f };
    const float MAIN_CAMERA_DISTANCE{ 2.5f };
}

void PlayScene::Start()
{
    // オブジェクト生成
    Light::Spawn(LIGHT_DIRECTION, LIGHT_AMBIENT, LIGHT_DIFFUSE, LIGHT_SPECULAR);
    SkyboxManager::SetSkybox(DEFAULT_SKYBOX);
    GameObjectPtr camera = MainCamera::Spawn(MAIN_CAMERA_OFFSET, MAIN_CAMERA_DISTANCE);
    GameObjectPtr player = Player::Spawn();

    // カメラのターゲットにプレイヤーを設定
    if (!player.expired())
    {
        auto controller = camera->GetComponentInParent<CameraController>();
        controller->SetTarget(player->Transform());
    }

    // UI生成
    auto hpCanvas = GameObjectManager::Instantiate("HPCanvas");
    hpCanvas->AddComponent<Canvas>();
    HPGauge::Spawn(hpCanvas);

#ifdef _DEBUG
    // デバッグ時のみ
    SafeArea::Spawn(); //UI調整用
#endif

    Skeleton::Spawn(Vector3{ 0, 0, 5 }, Vector3::Zero(), Vector3::One());
    //Mage::Spawn(Vector3{ 0, 0, 5 }, Vector3::Zero(), Vector3::One());

    // 当たり判定のレイヤー設定
    Physics::SetCollisionFlag(CollisionLayer::Player, CollisionLayer::PlayerAttack, false);
    Physics::SetCollisionFlag(CollisionLayer::Enemy, CollisionLayer::EnemyAttack, false);
    Physics::SetCollisionFlag(CollisionLayer::EnemyAttack, CollisionLayer::PlayerAttack, false);

    // debug stage
    auto stage = GameObjectManager::Instantiate("Stage");
    stage->Layer(CollisionLayer::Stage);
    stage->Tag("Obstacle");
    auto mr = stage->AddComponent<MeshRenderer>();
    mr->MeshID(4);
    auto mc = stage->AddComponent<MeshCollider>();
    mc->MeshID(4);
    mc->FlipNormals(true);
}

void PlayScene::End()
{

}
