#include "EnemyDeadEffect.h"
#include <Components/EffectSystem.h>
#include <GameObjectManager.h>
#include <GameObject.h>
#include <Vector3.h>

#include "../../Enum/EffectID.h"

using namespace Glib;

namespace
{
    const char* const EFFECT_OBJECT_NAME{ "EnemyDeadEffect" };
}

GameObjectPtr EnemyDeadEffect::Spawn(const Vector3& position)
{
    auto deadEfk = GameObjectManager::Instantiate(EFFECT_OBJECT_NAME);
    auto efkSystem = deadEfk->AddComponent<EffectSystem>();
    deadEfk->Transform()->Position(position);
    efkSystem->EffectID(EffectID::EnemyDead);
    efkSystem->DestoryOnFinish(true);
    efkSystem->PlayOnStart(true);

    return deadEfk;
}
