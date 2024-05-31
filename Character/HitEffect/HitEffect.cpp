#include "HitEffect.h"
#include <Components/AudioSource.h>
#include <Components/EffectSystem.h>
#include <GameObjectManager.h>
#include <GameObject.h>
#include <Vector3.h>

#include "../../Enum/EffectID.h"
#include "../../Enum/AudioID.h"
#include "../../Enum/AudioGroupID.h"

using namespace Glib;

namespace
{
    const char EFFECT_OBJECT_NAME[]{ "HitEffect" };
    constexpr float SE_PITCH{ 0.8f };
}

GameObjectPtr HitEffect::Spawn(const Vector3& position)
{
    auto hitEffect = GameObjectManager::Instantiate(EFFECT_OBJECT_NAME);
    hitEffect->Transform()->LocalPosition(position);
    hitEffect->Transform()->LocalScale(Vector3{ 0.7f });
    auto effect = hitEffect->AddComponent<EffectSystem>();
    effect->EffectID(EffectID::HitEffect);
    effect->EffectColor(Color{ 0.9f, 0.8f, 0.6f, 0.7f });
    effect->DestoryOnFinish(true);
    effect->PlayOnStart(true);

    return hitEffect;
}
