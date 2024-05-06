#include "PlayScene.h"
#include <Components/Canvas.h>
#include <Components/MeshRenderer.h>
#include <Components/MeshCollider.h>
#include <GameObject.h>
#include <GameObjectManager.h>
#include <SkyboxManager.h>
#include <Physics.h>
#include <Color.h>

#include "../Character/Light/Light.h"
#include "../Character/Camera/MainCamera.h"
#include "../Character/Player/Player.h"
#include "../Character/Enemy/Skeleton/Skeleton.h"
#include "../Character/Menu/SafeArea/SafeArea.h"
#include "../Character/UI/HPGauge/HPGauge.h"
#include "../Component/Camera/CameraController.h"
#include "../Enum/CollisionLayer.h"
#include <GameTimer.h>
#include "../Character/Projectile/MagicArrow.h"


using namespace Glib;

namespace
{
    const Vector3 LIGHT_DIRECTION{ 50.0f, -30.0f, 0.0f };
    const Color LIGHT_AMBIENT{ 0.7f, 0.7f, 0.7f, 1.0f };
    const Color LIGHT_DIFFUSE{ 0.7f, 0.7f, 0.7f, 1.0f };
    const Color LIGHT_SPECULAR{ 0.1f, 0.1f, 0.1f, 0.1f };
    const unsigned int DEFAULT_SKYBOX{ 0 };
    const Vector3 MAIN_CAMERA_OFFSET{ 0.0f, 1.6f, 0.0f };
    const float MAIN_CAMERA_DISTANCE{ 2.5f };
}

void PlayScene::Start()
{
    Light::Spawn(LIGHT_DIRECTION, LIGHT_AMBIENT, LIGHT_DIFFUSE, LIGHT_SPECULAR);
    SkyboxManager::SetSkybox(DEFAULT_SKYBOX);
    GameObjectPtr camera = MainCamera::Spawn(MAIN_CAMERA_OFFSET, MAIN_CAMERA_DISTANCE);
    GameObjectPtr player = Player::Spawn();
    auto hpCanvas = GameObjectManager::Instantiate("HPCanvas");
    hpCanvas->AddComponent<Canvas>();
    HPGauge::Spawn(hpCanvas);
    Skeleton::Spawn(Vector3{ 0, 0, 5 }, Vector3::Zero(), Vector3::One());

    Physics::SetCollisionFlag(CollisionLayer::Player, CollisionLayer::PlayerAttack, false);
    Physics::SetCollisionFlag(CollisionLayer::Enemy, CollisionLayer::EnemyAttack, false);
    Physics::SetCollisionFlag(CollisionLayer::EnemyAttack, CollisionLayer::PlayerAttack, false);

    if (!player.expired())
    {
        auto controller = camera->GetComponentInParent<CameraController>();
        // カメラのターゲットにプレイヤーを設定
        controller->SetTarget(player->Transform());
    }

    MagicArrow::Spawn(Vector3{ 0.0f, 2.0f, 5.0f }, 0.0f, player);

    // debug stage
    auto stage = GameObjectManager::Instantiate("Stage");
    stage->Layer(CollisionLayer::Stage);
    stage->Tag("Obstacle");
    auto mr = stage->AddComponent<MeshRenderer>();
    mr->MeshID(4);
    auto mc = stage->AddComponent<MeshCollider>();
    mc->MeshID(4);
    mc->FlipNormals(true);

    SafeArea::Spawn();
}

void PlayScene::End()
{

}
