#include "MagicArrow.h"
#include <Components/Rigidbody.h>
#include <Components/CapsuleCollider.h>
#include <Components/EffectSystem.h>
#include <GameObject.h>
#include <GameObjectManager.h>

#include "../../Component/Projectile/Projectile.h"
#include "../../Component/Common/AttackColliderController.h"
#include "../../Enum/EffectID.h"
#include "../../Enum/CollisionLayer.h"

using namespace Glib;

namespace
{
    const Vector3 EFFECT_ANGLE{ 0.0f, 180.0f, 0.0f };
    constexpr float ROTATE_SPEED{ 10.0f };
}

void MagicArrow::Spawn(const Vector3& position, float speed, const GameObjectPtr& target)
{
    auto arrow = GameObjectManager::Instantiate("MagicArrow");
    arrow->Transform()->Position(position);
    arrow->Layer(CollisionLayer::EnemyAttack);

    auto rb = arrow->AddComponent<Rigidbody>();
    rb->Constraints(RigidbodyConstraints::FreezeRotation);
    rb->UseGravity(false);

    auto collider = arrow->AddComponent<CapsuleCollider>();
    collider->IsTrigger(true);

    auto controller = arrow->AddComponent<AttackColliderController>(collider, true);
    controller->SetAttackActive(true);
    controller->SetAttackPower(20);

    auto arrowEffect = GameObjectManager::Instantiate("ArrowEffect");
    auto effect = arrowEffect->AddComponent<EffectSystem>();
    effect->EffectID(EffectID::MagicArrow);
    effect->PlayOnStart(true);
    effect->Loop(true);
    arrowEffect->Transform()->Parent(arrow->Transform());
    arrowEffect->Transform()->LocalEulerAngles(EFFECT_ANGLE);

    auto projectile = arrow->AddComponent<Projectile>(target->Transform(), 2.0f);
    projectile->MoveSpeed(speed);
    projectile->RotateSpeed(ROTATE_SPEED);
}
