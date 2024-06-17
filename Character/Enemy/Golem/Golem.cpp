#include "Golem.h"
#include <GameObject.h>
#include <GameObjectManager.h>
#include <Components/Transform.h>
#include <Components/SkinnedMeshRenderer.h>
#include <Components/Animator.h>
#include <Components/AudioSource.h>
#include <Components/EffectSystem.h>
#include <Components/Rigidbody.h>
#include <Components/BoxCollider.h>
#include <Components/SphereCollider.h>

#include "../../../Component/Common/Rotator.h"
#include "../../../Component/Common/AttackColliderController.h"
#include "../../../Component/Common/Damageable.h"
#include "../../../Component/StateMachine/StateBehavior.h"
#include "../../../Component/Enemy/CharacterSearcher.h"
#include "../../../Component/Enemy/State/EnemyAttackState.h"
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

using namespace Glib;

namespace
{
    constexpr float SEARCH_FOV{ 90.0f };
    constexpr float MASS{ 20.0f };
    const Vector3 BODY_COLLIDER_CENTER{ 0.0f, 1.3f, 0.0f };
    const Vector3 BODY_COLLIDER_SIZE{ 3.24f, 2.86f, 1.0f };

    const Vector3 ATK_COLLIDER_POSITION{ 0.0f, 1.48f, 1.43f };
    const Vector3 ATK_COLLIDER_SIZE{ 0.20f, 1.46f, 0.29f };

    constexpr float ATK_COLLIDER_RADIUS{ 1.25f };
}

GameObjectPtr Golem::Spawn(const Vector3& position, const Vector3& euler, const Vector3& scale)
{
    auto golem = GameObjectManager::Instantiate("EnemyGolem");
    golem->Layer(CollisionLayer::Enemy);
    golem->Transform()->Position(position);
    golem->Transform()->EulerAngles(euler);
    golem->Transform()->Scale(scale);
    auto skinned = golem->AddComponent<SkinnedMeshRenderer>();
    skinned->MeshID(MeshID::Golem);
    golem->AddComponent<Animator>();
    golem->AddComponent<AudioSource>();
    auto rigidbody = golem->AddComponent<Rigidbody>();
    rigidbody->Constraints(RigidbodyConstraints::FreezeRotation);
    rigidbody->Mass(MASS);
    auto collider = golem->AddComponent<BoxCollider>();
    collider->Size(BODY_COLLIDER_SIZE);
    collider->Center(BODY_COLLIDER_CENTER);
    collider->IsVisible(true);

    auto attackColliderObj = GameObjectManager::Instantiate("RightATKCollider");
    attackColliderObj->Layer(CollisionLayer::EnemyAttack);
    attackColliderObj->Transform()->Parent(golem->Transform());
    attackColliderObj->Transform()->LocalPosition(ATK_COLLIDER_POSITION);

    auto attackRb = attackColliderObj->AddComponent<Rigidbody>();
    auto attackcollider = attackColliderObj->AddComponent<SphereCollider>();
    attackcollider->Radius(ATK_COLLIDER_RADIUS);
    attackRb->IsKinematic(true);
    attackcollider->IsTrigger(true);
    attackcollider->IsVisible(true);

    auto controller = attackColliderObj->AddComponent<AttackColliderController>();
    controller->AddCollider(attackcollider);
    GameObjectPtr player = GameObjectManager::Find(ObjectName::Player);
    golem->AddComponent<Rotator>()->Speed(1.7f);
    golem->AddComponent<CharacterSearcher>(SEARCH_FOV, 100.0f, 10.0f, player);
    golem->AddComponent<Damageable>(120, 120, 15, EnemyState::Damage, EnemyState::Dead);

    auto stateBehavior = golem->AddComponent<StateBehavior>();

    EnemyAttackState::Parameter attackParam1;
    attackParam1.nextStateID = EnemyState::Selector;
    attackParam1.power = 20;
    attackParam1.duration = 1.2f;
    attackParam1.attackTime = ValidityTimer{ 0.3f, 0.3f };
    auto golemAttack1 = golem->AddComponent<EnemyAttackState>(attackParam1);
    golemAttack1->SetAnimationInfo(AnimationInfo{ AnimationID::GolemAttack1 });
    stateBehavior->AddState(golemAttack1, EnemyState::MaelstromAttack);

    EnemyAttackState::Parameter attackParam2;
    attackParam2.nextStateID = EnemyState::Selector;
    attackParam2.power = 10;
    attackParam2.duration = 1.5f;
    attackParam2.attackTime = ValidityTimer{ 0.2f, 0.4f };
    auto golemAttack2 = golem->AddComponent<EnemyAttackState>(attackParam2);
    golemAttack2->SetAnimationInfo(AnimationInfo{ AnimationID::GolemAttack2 });
    stateBehavior->AddState(golemAttack2, EnemyState::MeleeAttack);

    auto golemSearch = golem->AddComponent<EnemySearchState>(0.016f);
    golemSearch->SetAnimationInfo(AnimationInfo{ AnimationID::GolemIdle, 0.0f, 0.1f, 1.0f, true });
    stateBehavior->AddState(golemSearch, EnemyState::Search);

    EnemyChaseState::Parameter chaseParam;
    chaseParam.completeDistance = 3.0f;
    chaseParam.moveSpeed = 10.0f;
    chaseParam.moveForceMultiplier = 10.0f;
    auto golemChase = golem->AddComponent<EnemyChaseState>(chaseParam);
    golemChase->AddNextState(EnemyState::MaelstromAttack);
    golemChase->AddNextState(EnemyState::MeleeAttack);
    golemChase->SetAnimationInfo(AnimationInfo{ AnimationID::GolemMove, 0.0f, 0.1f, 1.0f, true });
    stateBehavior->AddState(golemChase, EnemyState::Chase);

    EnemyDamageState::Parameter damageParam;
    damageParam.nextStateID = EnemyState::Selector;
    damageParam.duration = 1.3f;
    damageParam.moveSpeed = 1.0f;
    damageParam.moveForceMultiplier = 20.0f;
    auto golemDamage = golem->AddComponent<EnemyDamageState>(damageParam);
    golemDamage->SetAnimationInfo(AnimationInfo{ AnimationID::GolemDamage, 0.0f, 0.8f, 2.0f, false });
    stateBehavior->AddState(golemDamage, EnemyState::Damage);

    auto golemDead = golem->AddComponent<EnemyDeadState>(3.0f);
    golemDead->SetAnimationInfo(AnimationInfo{ AnimationID::GolemIdle });
    stateBehavior->AddState(golemDead, EnemyState::Dead);

    auto golemSelector = golem->AddComponent<EnemySelectorState>();
    golemSelector->SetAnimationInfo(AnimationInfo{ AnimationID::GolemIdle, 0.0f, 0.1f, 1.0f, true });
    golemSelector->AddNextState(EnemyState::Chase);
    stateBehavior->AddState(golemSelector, EnemyState::Selector);

    stateBehavior->ChangeState(EnemyState::Selector);

    return golem;
}
