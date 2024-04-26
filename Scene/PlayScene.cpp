#include "PlayScene.h"
#include <GameObject.h>
#include <GameObjectManager.h>
#include <Components/Transform.h>
#include <Components/MeshCollider.h>
#include <Components/MeshRenderer.h>
#include <Components/DirectionalLight.h>
#include <SkyboxManager.h>
#include <Physics.h>
#include <Color.h>

#include "../Character/Camera/MainCamera.h"
#include "../Character/Player/Player.h"
#include "../Character/Enemy/Skeleton/Skeleton.h"
#include "../Constant/GameObjectName.h"
#include "../Component/Camera/CameraController.h"
#include "../Enum/CollisionLayer.h"

using namespace Glib;

namespace
{
    const Vector3 LIGHT_DIRECTION{ 30.0f, 40.0f, 0.0f };
    const Color LIGHT_AMBIENT{ 0.7f, 0.7f, 0.7f, 1.0f };
    const Color LIGHT_DIFFUSE{ 0.7f, 0.7f, 0.7f, 1.0f };
    const Color LIGHT_SPECULAR{ 0.5f, 0.5f, 0.5f, 0.5f };
    const unsigned int DEFAULT_SKYBOX{ 0 };
    const Vector3 MAIN_CAMERA_OFFSET{ 0.0f, 1.6f, 0.0f };
    const float MAIN_CAMERA_DISTANCE{ 2.5f };
}

void PlayScene::Start()
{
    auto light = GameObjectManager::Instantiate(ObjectName::Light)->AddComponent<DirectionalLight>();
    light->Ambient(LIGHT_AMBIENT);
    light->Diffuse(LIGHT_DIFFUSE);
    light->Specular(LIGHT_SPECULAR);
    light->GameObject()->Transform()->EulerAngles(LIGHT_DIRECTION);

    SkyboxManager::SetSkybox(DEFAULT_SKYBOX);
    GameObjectPtr camera = MainCamera::Spawn(MAIN_CAMERA_OFFSET, MAIN_CAMERA_DISTANCE);
    GameObjectPtr player = Player::Spawn();
    Skeleton::Spawn(Vector3{ 0, 0, 5 }, Vector3::Zero(), Vector3::One());

    Physics::SetCollisionFlag(CollisionLayer::Player, CollisionLayer::PlayerAttack, false);
    Physics::SetCollisionFlag(CollisionLayer::Enemy, CollisionLayer::EnemyAttack, false);
    Physics::SetCollisionFlag(CollisionLayer::EnemyAttack, CollisionLayer::PlayerAttack, false);

    if (!player.expired())
    {
        auto controller = camera->GetComponentInParent<CameraController>();
        controller->SetTarget(player->Transform()); // カメラにPlayerを注目するように設定
    }

    auto stage = GameObjectManager::Instantiate("Stage");
    stage->Layer(CollisionLayer::Stage);
    stage->Tag("Obstacle");
    auto mr = stage->AddComponent<MeshRenderer>();
    mr->MeshID(2);
    auto mc = stage->AddComponent<MeshCollider>();
    mc->MeshID(2);
    mc->FlipNormals(true);
}

void PlayScene::End()
{

}
