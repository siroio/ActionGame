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
    auto deadEfk = GameObjectManager::Instantiate(EFFECT_OBJECT_NAME);
    deadEfk->Transform()->LocalPosition(position);
    deadEfk->Transform()->LocalScale(Vector3{ 0.7f });
    auto effect = deadEfk->AddComponent<EffectSystem>();
    effect->EffectID(EffectID::HitEffect);
    effect->EffectColor(Color{ 0.9f, 0.8f, 0.6f, 0.7f });
    effect->DestoryOnFinish(true);
    effect->PlayOnStart(true);

    //auto sound = deadEfk->AddComponent<AudioSource>();
    //sound->AudioID(AudioID::EnemyDead);
    //sound->Is3DSound(true);
    //sound->PlayOnStart(true);
    //sound->Pitch(SE_PITCH);
    //sound->SetGroup(AudioGroupID::SE);

    return deadEfk;
}
