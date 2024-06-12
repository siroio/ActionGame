#include "Stage.h"
#include <Components/MeshRenderer.h>
#include <Components/MeshCollider.h>
#include <GameObject.h>
#include <GameObjectManager.h>

#include "../../Constant/ObjectTag.h"
#include "../../Enum/CollisionLayer.h"
#include "../../Enum/MeshID.h"

using namespace Glib;

namespace
{
    void CreateStageMesh(const GameObjectPtr& parent, unsigned int id)
    {
        auto stage = GameObjectManager::Instantiate("Parts: " + std::to_string(id));
        stage->Transform()->Parent(parent->Transform());
        stage->Layer(CollisionLayer::Stage);
        stage->Tag(GameTag::OBSTACLE);
        auto mesh = stage->AddComponent<MeshRenderer>();
        mesh->MeshID(id);
        auto collider = stage->AddComponent<MeshCollider>();
        collider->MeshID(id);
    }
}

void Stage::Spawn()
{
    auto stage = GameObjectManager::Instantiate("Stage");
    CreateStageMesh(stage, MeshID::Ground);
    CreateStageMesh(stage, MeshID::Mountain);
    CreateStageMesh(stage, MeshID::WALL_1);
    CreateStageMesh(stage, MeshID::WALL_2);
    CreateStageMesh(stage, MeshID::WALL_3);
    CreateStageMesh(stage, MeshID::WALL_4);
    CreateStageMesh(stage, MeshID::WALL_5);
}
