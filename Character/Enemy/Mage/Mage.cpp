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
    auto mage = GameObjectManager::Instantiate("EnemyMage");
    mage->Layer(CollisionLayer::Enemy);
    mage->Transform()->Position(position);
    mage->Transform()->EulerAngles(euler);
    mage->Transform()->Scale(scale);
    auto skinned = mage->AddComponent<SkinnedMeshRenderer>();
    skinned->MeshID(MeshID::Mage);
    mage->AddComponent<Animator>();
    mage->AddComponent<AudioSource>();
    auto rigidbody = mage->AddComponent<Rigidbody>();
    rigidbody->Constraints(RigidbodyConstraints::FreezeRotation);
    auto collider = mage->AddComponent<CapsuleCollider>();
    collider->Center(BODY_COLLIDER_CENTER);
    collider->Height(BODY_COLLIDER_HEIGHT);
    collider->Radius(BODY_COLLIDER_RADIUS);

    GameObjectPtr player = GameObjectManager::Find(ObjectName::Player);
    mage->AddComponent<Rotator>();
    mage->AddComponent<CharacterSearcher>(SEARCH_FOV, 100.0f, 2.0f, player);
    mage->AddComponent<Damageable>(15, 15, 0, EnemyState::Damage, EnemyState::Dead);

    auto stateBehavior = mage->AddComponent<StateBehavior>();

    EnemyProjectileAttackState::Parameter attackParam{};
    attackParam.nextStateID = EnemyState::Selector;
    attackParam.spawn = MagicArrow::Spawn;
    attackParam.spawnPoint = Vector3{ 0.0f, 2.3f, -0.2f };
    attackParam.flySpeed = 10.0f;
    attackParam.duration = 2.0f;
    attackParam.delay = 1.0f;
    auto mgAttack = mage->AddComponent<EnemyProjectileAttackState>(attackParam);
    mgAttack->SetAnimationInfo(AnimationInfo{ AnimationID::MageAttack });
    stateBehavior->AddState(mgAttack, EnemyState::ProjectileAttack);

    auto mgSearch = mage->AddComponent<EnemySearchState>(0.016f);
    mgSearch->SetAnimationInfo(AnimationInfo{ AnimationID::MageIdle, 0.0f, 0.1f, true });
    stateBehavior->AddState(mgSearch, EnemyState::Search);

    EnemyChaseState::Parameter chaseParam{};
    chaseParam.completeDistance = 10.0f;
    chaseParam.moveSpeed = 3.0f;
    chaseParam.moveForceMultiplier = 20.0f;
    auto mgChase = mage->AddComponent<EnemyChaseState>(chaseParam);
    mgChase->AddNextState(EnemyState::ProjectileAttack);
    mgChase->SetAnimationInfo(AnimationInfo{ AnimationID::MageMove, 0.0f, 0.1f, true });
    stateBehavior->AddState(mgChase, EnemyState::Chase);

    EnemyDamageState::Parameter damageParam{};
    damageParam.nextStateID = EnemyState::Selector;
    damageParam.duration = 0.3f;
    damageParam.moveSpeed = 1.0f;
    damageParam.moveForceMultiplier = 20.0f;
    auto mgDamage = mage->AddComponent<EnemyDamageState>(damageParam);
    mgDamage->SetAnimationInfo(AnimationInfo{ AnimationID::MageDamage });
    stateBehavior->AddState(mgDamage, EnemyState::Damage);

    auto mgDead = mage->AddComponent<EnemyDeadState>(1.12f);
    mgDead->SetAnimationInfo(AnimationInfo{ AnimationID::MageDeath });
    stateBehavior->AddState(mgDead, EnemyState::Dead);

    auto mgSelector = mage->AddComponent<EnemySelectorState>();
    mgSelector->SetAnimationInfo(AnimationInfo{ AnimationID::MageIdle, 0.0f, 0.1f, true });
    mgSelector->AddNextState(EnemyState::Search);
    stateBehavior->AddState(mgSelector, EnemyState::Selector);

    stateBehavior->ChangeState(EnemyState::Selector);
    return mage;
}
