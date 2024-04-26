#include "Skeleton.h"
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
#include "../../../Utility/ReceptionTimer.h"

using namespace Glib;

namespace
{
    constexpr float SEARCH_FOV{ 60.0f };
    const Vector3 BODY_COLLIDER_CENTER{ 0.0f, 0.87f, 0.0f };
    constexpr float BODY_COLLIDER_HEIGHT{ 0.23f };
    constexpr float BODY_COLLIDER_RADIUS{ 0.65f };
    const Vector3 ATK_COLLIDER_ANGLES{ 18.0f, 0.0f, 350.0f };
    const Vector3 ATK_COLLIDER_POSITION{ 0.20f, 0.97f, 0.31f };
    const Vector3 ATK_COLLIDER_SIZE{ 0.20f, 1.46f, 0.29f };
}

GameObjectPtr Skeleton::Spawn(const Vector3& position, const Vector3& euler, const Vector3& scale)
{
    auto skeleton = GameObjectManager::Instantiate("EnemySkeleton");
    skeleton->Transform()->Position(position);
    skeleton->Transform()->EulerAngles(euler);
    skeleton->Transform()->Scale(scale);
    auto skinned = skeleton->AddComponent<SkinnedMeshRenderer>();
    skinned->MeshID(MeshID::Skeleton);
    skeleton->AddComponent<Animator>();
    skeleton->AddComponent<AudioSource>();
    auto rigidbody = skeleton->AddComponent<Rigidbody>();
    rigidbody->Constraints(RigidbodyConstraints::FreezeRotation);
    auto collider = skeleton->AddComponent<CapsuleCollider>();
    collider->Center(BODY_COLLIDER_CENTER);
    collider->Height(BODY_COLLIDER_HEIGHT);
    collider->Radius(BODY_COLLIDER_RADIUS);


    auto enemyAtk = GameObjectManager::Instantiate("EnemyATKCollider");
    auto parent = skeleton->Transform()->Find("Weapon");
    enemyAtk->Transform()->Parent(parent);
    auto atkRb = enemyAtk->AddComponent<Rigidbody>();
    auto atkc = enemyAtk->AddComponent<BoxCollider>();
    atkRb->IsKinematic(true);
    atkc->IsTrigger(true);
    enemyAtk->Transform()->Position(ATK_COLLIDER_POSITION);
    enemyAtk->Transform()->EulerAngles(ATK_COLLIDER_ANGLES);
    enemyAtk->Transform()->Scale(ATK_COLLIDER_SIZE);
    enemyAtk->AddComponent<AttackColliderController>(atkc);

    GameObjectPtr player = GameObjectManager::Find(ObjectName::Player);
    skeleton->AddComponent<Rotator>();
    skeleton->AddComponent<CharacterSearcher>(SEARCH_FOV, 100.0f, player);
    skeleton->AddComponent<Damageable>(1, 1, 3, EnemyState::Damage, EnemyState::Dead);

    auto stateBehavior = skeleton->AddComponent<StateBehavior>();

    EnemyAttackState::Parameter attackParam{
        EnemyState::Selector,
        3,
        1.0f,
        ReceptionTimer{ 0.1f, 0.1f },
    };
    auto skAttack = skeleton->AddComponent<EnemyAttackState>(attackParam);
    skAttack->SetAnimationInfo(AnimationInfo{ AnimationID::SkeletonAttack });
    stateBehavior->AddState(skAttack, EnemyState::MeleeAttack);

    auto skSearch = skeleton->AddComponent<EnemySearchState>(0.15f);
    skSearch->SetAnimationInfo(AnimationInfo{ AnimationID::SkeletonIdle });
    stateBehavior->AddState(skSearch, EnemyState::Search);

    EnemyChaseState::Parameter chaseParam{
        2.0f,
        3.0f,
        20.0f,
    };
    auto skChase = skeleton->AddComponent<EnemyChaseState>(chaseParam);
    skChase->AddNextState(EnemyState::MeleeAttack);
    skChase->SetAnimationInfo(AnimationInfo{ AnimationID::SkeletonMove, 0.0f, 0.1f, true });
    stateBehavior->AddState(skChase, EnemyState::Chase);

    EnemyDamageState::Parameter damageParam{
        EnemyState::Selector,
        0.7f,
        0.3f,
        20.0f,
    };
    auto skDamage = skeleton->AddComponent<EnemyDamageState>(damageParam);
    skDamage->SetAnimationInfo(AnimationInfo{ AnimationID::SkeletonDamage });
    stateBehavior->AddState(skDamage, EnemyState::Damage);

    auto skDead = skeleton->AddComponent<EnemyDeadState>(1.12f);
    skDead->SetAnimationInfo(AnimationInfo{ AnimationID::SkeletonDeath });
    stateBehavior->AddState(skDead, EnemyState::Dead);

    auto skSelector = skeleton->AddComponent<EnemySelectorState>();
    skSelector->AddNextState(EnemyState::Search);
    stateBehavior->AddState(skSelector, EnemyState::Selector);

    stateBehavior->ChangeState(EnemyState::Search);
    return skeleton;
}
