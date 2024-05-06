#include "Mage.h"
#include <GameObject.h>
#include <GameObjectManager.h>
#include <Components/Transform.h>
#include <Components/SkinnedMeshRenderer.h>
#include <Components/Animator.h>
#include <Components/AudioSource.h>
#include <Components/EffectSystem.h>
#include <Components/Rigidbody.h>
#include <Components/CapsuleCollider.h>
#include <Components/BoxCollider.h>

#include "../../../Component/Common/Rotator.h"
#include "../../../Component/Common/AttackColliderController.h"
#include "../../../Component/Common/Damageable.h"
#include "../../../Component/StateMachine/StateBehavior.h"
#include "../../../Component/Enemy/CharacterSearcher.h"
#include "../../../Component/Enemy/State/EnemyProjectileAttackState.h"
#include "../../../Component/Enemy/State/EnemyChaseState.h"
#include "../../../Component/Enemy/State/EnemyDamageState.h"
#include "../../../Component/Enemy/State/EnemyDeadState.h"
#include "../../../Component/Enemy/State/EnemySearchState.h"
#include "../../../Component/Enemy/State/EnemySelectorState.h"
#include "../../../Constant/GameObjectName.h"
#include "../../../Enum/State/EnemyState.h"
#include "../../../Enum/AnimationID.h"
#include "../../../Enum/MeshID.h"
#include "../../../Enum/CollisionLayer.h"
#include "../../Projectile/MagicArrow.h"

using namespace Glib;

namespace
{
    constexpr float SEARCH_FOV{ 80.0f };
    const Vector3 BODY_COLLIDER_CENTER{ 0.0f, 0.87f, 0.0f };
    constexpr float BODY_COLLIDER_HEIGHT{ 0.23f };
    constexpr float BODY_COLLIDER_RADIUS{ 0.65f };
    const Vector3 ATK_COLLIDER_ANGLES{ 18.0f, 0.0f, 350.0f };
    const Vector3 ATK_COLLIDER_POSITION{ 0.20f, 0.97f, 0.31f };
    const Vector3 ATK_COLLIDER_SIZE{ 0.20f, 1.46f, 0.29f };
    constexpr char ATK_COLLIDER_PARENT[]{ "Weapon" };
}

GameObjectPtr Mage::Spawn(const Vector3& position, const Vector3& euler, const Vector3& scale)
{
    auto skeleton = GameObjectManager::Instantiate("EnemyMage");
    skeleton->Layer(CollisionLayer::Enemy);
    skeleton->Transform()->Position(position);
    skeleton->Transform()->EulerAngles(euler);
    skeleton->Transform()->Scale(scale);
    auto skinned = skeleton->AddComponent<SkinnedMeshRenderer>();
    skinned->MeshID(MeshID::Mage);
    skeleton->AddComponent<Animator>();
    skeleton->AddComponent<AudioSource>();
    auto rigidbody = skeleton->AddComponent<Rigidbody>();
    rigidbody->Constraints(RigidbodyConstraints::FreezeRotation);
    auto collider = skeleton->AddComponent<CapsuleCollider>();
    collider->Center(BODY_COLLIDER_CENTER);
    collider->Height(BODY_COLLIDER_HEIGHT);
    collider->Radius(BODY_COLLIDER_RADIUS);

    auto enemyAtk = GameObjectManager::Instantiate("EnemyATKCollider");
    enemyAtk->Layer(CollisionLayer::EnemyAttack);
    auto parent = skeleton->Transform()->Find(ATK_COLLIDER_PARENT);
    enemyAtk->Transform()->Parent(parent);
    auto atkRb = enemyAtk->AddComponent<Rigidbody>();
    auto atkc = enemyAtk->AddComponent<BoxCollider>();
    atkRb->IsKinematic(true);
    atkc->IsTrigger(true);
    atkc->IsVisible(true);
    enemyAtk->Transform()->LocalPosition(ATK_COLLIDER_POSITION);
    enemyAtk->Transform()->LocalEulerAngles(ATK_COLLIDER_ANGLES);
    enemyAtk->Transform()->LocalScale(ATK_COLLIDER_SIZE);
    enemyAtk->AddComponent<AttackColliderController>(atkc);

    GameObjectPtr player = GameObjectManager::Find(ObjectName::Player);
    skeleton->AddComponent<Rotator>();
    skeleton->AddComponent<CharacterSearcher>(SEARCH_FOV, 100.0f, player);
    skeleton->AddComponent<Damageable>(30, 30, 3, EnemyState::Damage, EnemyState::Dead);

    auto stateBehavior = skeleton->AddComponent<StateBehavior>();

    EnemyProjectileAttackState::Parameter attackParam{
        EnemyState::Selector,
        MagicArrow::Spawn,
        Vector3{ 0.0f, 2.3f, -0.2f },
        10.0f,
        2.0f,
        1.0f,
    };
    auto skAttack = skeleton->AddComponent<EnemyProjectileAttackState>(attackParam);
    skAttack->SetAnimationInfo(AnimationInfo{ AnimationID::MageAttack });
    stateBehavior->AddState(skAttack, EnemyState::ProjectileAttack);

    auto skSearch = skeleton->AddComponent<EnemySearchState>(0.016f);
    skSearch->SetAnimationInfo(AnimationInfo{ AnimationID::MageIdle, 0.0f, 0.1f, true });
    stateBehavior->AddState(skSearch, EnemyState::Search);

    EnemyChaseState::Parameter chaseParam{
        10.0f,
        3.0f,
        20.0f,
    };
    auto skChase = skeleton->AddComponent<EnemyChaseState>(chaseParam);
    skChase->AddNextState(EnemyState::MeleeAttack);
    skChase->SetAnimationInfo(AnimationInfo{ AnimationID::MageMove, 0.0f, 0.1f, true });
    stateBehavior->AddState(skChase, EnemyState::Chase);

    EnemyDamageState::Parameter damageParam{
        EnemyState::Selector,
        0.7f,
        0.3f,
        20.0f,
    };
    auto skDamage = skeleton->AddComponent<EnemyDamageState>(damageParam);
    skDamage->SetAnimationInfo(AnimationInfo{ AnimationID::MageDamage });
    stateBehavior->AddState(skDamage, EnemyState::Damage);

    auto skDead = skeleton->AddComponent<EnemyDeadState>(1.12f);
    skDead->SetAnimationInfo(AnimationInfo{ AnimationID::MageDeath });
    stateBehavior->AddState(skDead, EnemyState::Dead);

    auto skSelector = skeleton->AddComponent<EnemySelectorState>();
    skSelector->SetAnimationInfo(AnimationInfo{ AnimationID::SkeletonIdle, 0.0f, 0.1f, true });
    skSelector->AddNextState(EnemyState::Search);
    stateBehavior->AddState(skSelector, EnemyState::Selector);

    stateBehavior->ChangeState(EnemyState::Selector);
    return skeleton;
}
