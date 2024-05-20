#include "Golem.h"
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
    const Vector3 BODY_COLLIDER_CENTER{ 0.0f, 1.43f, 0.0f };
    const Vector3 BODY_COLLIDER_SIZE{ 1.6f, 2.86f, 1.0f };

    const Vector3 ATK_COLLIDER_ANGLES{ 18.0f, 0.0f, 350.0f };
    const Vector3 ATK_COLLIDER_POSITION{ 0.20f, 0.97f, 0.31f };
    const Vector3 ATK_COLLIDER_SIZE{ 0.20f, 1.46f, 0.29f };

    constexpr char ATK_COLLIDER_RIGHT_PARENT[]{ "hand4.R" };
    constexpr char ATK_COLLIDER_LEFT_PARENT[]{ "hand4.L" };
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
    rigidbody->Mass(20.0f);
    auto collider = golem->AddComponent<BoxCollider>();
    collider->Size(BODY_COLLIDER_SIZE);
    collider->Center(BODY_COLLIDER_CENTER);
    collider->IsVisible(true);

    GameObjectPtr player = GameObjectManager::Find(ObjectName::Player);
    golem->AddComponent<Rotator>();
    golem->AddComponent<CharacterSearcher>(SEARCH_FOV, 100.0f, 10.0f, player);
    golem->AddComponent<Damageable>(120, 120, 3, EnemyState::Damage, EnemyState::Dead);

    auto stateBehavior = golem->AddComponent<StateBehavior>();

    EnemyAttackState::Parameter attackParam;
    attackParam.nextStateID = EnemyState::Selector;
    attackParam.power = 3;
    attackParam.duration = 1.0f;
    attackParam.attackTime = ValidityTimer{ 0.5f, 0.3f };
    auto skAttack = golem->AddComponent<EnemyAttackState>(attackParam);
    skAttack->SetAnimationInfo(AnimationInfo{ AnimationID::GolemAttack1 });
    //stateBehavior->AddState(skAttack, EnemyState::MeleeAttack);

    auto skSearch = golem->AddComponent<EnemySearchState>(0.016f);
    skSearch->SetAnimationInfo(AnimationInfo{ AnimationID::GolemIdle, 0.0f, 0.1f, 1.0f, true });
    stateBehavior->AddState(skSearch, EnemyState::Search);

    EnemyChaseState::Parameter chaseParam;
    chaseParam.completeDistance = 2.0f;
    chaseParam.moveSpeed = 1.3f;
    chaseParam.moveForceMultiplier = 10.0f;
    auto skChase = golem->AddComponent<EnemyChaseState>(chaseParam);
    //skChase->AddNextState(EnemyState::MeleeAttack);
    skChase->SetAnimationInfo(AnimationInfo{ AnimationID::GolemMove, 0.0f, 0.1f, 1.0f, true });
    stateBehavior->AddState(skChase, EnemyState::Chase);

    EnemyDamageState::Parameter damageParam;
    damageParam.nextStateID = EnemyState::Selector;
    damageParam.duration = 0.6f;
    damageParam.moveSpeed = 1.0f;
    damageParam.moveForceMultiplier = 20.0f;
    auto skDamage = golem->AddComponent<EnemyDamageState>(damageParam);
    skDamage->SetAnimationInfo(AnimationInfo{ AnimationID::GolemDamage, 0.0f, 0.4f, 2.0f, false });
    stateBehavior->AddState(skDamage, EnemyState::Damage);

    auto skDead = golem->AddComponent<EnemyDeadState>(3.0f);
    skDead->SetAnimationInfo(AnimationInfo{ AnimationID::GolemIdle });
    stateBehavior->AddState(skDead, EnemyState::Dead);

    auto skSelector = golem->AddComponent<EnemySelectorState>();
    skSelector->SetAnimationInfo(AnimationInfo{ AnimationID::GolemIdle, 0.0f, 0.1f, 1.0f, true });
    skSelector->AddNextState(EnemyState::Chase);
    stateBehavior->AddState(skSelector, EnemyState::Selector);

    stateBehavior->ChangeState(EnemyState::Selector);

    return golem;
}
