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
#include "../Constant/GameObjectName.h"
#include "../Component/Camera/CameraController.h"
#include "../Enum/CollisionLayer.h"

using namespace Glib;

namespace
{
    const Vector3 LIGHT_DIRECTION{ 30.0f, 40.0f, 0.0f };
    const Color LIGHT_AMBIENT{ 0.7f, 0.7f, 0.7f, 1.0f };
    const Color LIGHT_DIFFUSE{ 0.7f, 0.7f, 0.7f, 1.0f };
    const unsigned int DEFAULT_SKYBOX{ 0 };
    const Vector3 MAIN_CAMERA_OFFSET{ 0.0f, 1.6f, 0.0f };
    const float MAIN_CAMERA_DISTANCE{ 2.5f };
}

void PlayScene::Start()
{
    auto light = GameObjectManager::Instantiate(ObjectName::Light)
        ->AddComponent<DirectionalLight>();
    light->Ambient(LIGHT_AMBIENT);
    light->Diffuse(LIGHT_DIFFUSE);
    light->GameObject()->Transform()->EulerAngles(LIGHT_DIRECTION);

    SkyboxManager::SetSkybox(DEFAULT_SKYBOX);
    MainCamera::Create(MAIN_CAMERA_OFFSET, MAIN_CAMERA_DISTANCE);
    Player::Create();

    Physics::SetCollisionFlag(CollisionLayer::Player, CollisionLayer::PlayerAttack, false);
    Physics::SetCollisionFlag(CollisionLayer::Enemy, CollisionLayer::EnemyAttack, false);
    Physics::SetCollisionFlag(CollisionLayer::EnemyAttack, CollisionLayer::PlayerAttack, false);

    auto player = GameObjectManager::Find(ObjectName::Player);
    if (!player.expired())
    {
        auto camera =
            GameObjectManager::Find(ObjectName::Camera)->GetComponentInParent<CameraController>();
        camera->SetTarget(player->Transform());
    }

    auto stage = GameObjectManager::Instantiate("Stage");
    stage->Layer(CollisionLayer::Stage);
    auto mr = stage->AddComponent<MeshRenderer>();
    mr->MeshID(1);
    auto mc = stage->AddComponent<MeshCollider>();
    mc->MeshID(1);
    mc->FlipNormals(true);
}

void PlayScene::End()
{

}
