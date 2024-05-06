#include "Player.h"
#include <GameObjectManager.h>
#include <GameObject.h>
#include <Components/SkinnedMeshRenderer.h>
#include <Components/Animator.h>
#include <Components/AudioSource.h>
#include <Components/EffectSystem.h>
#include <Components/Rigidbody.h>
#include <Components/CapsuleCollider.h>
#include <Components/BoxCollider.h>

#include "../../Enum/State/PlayerState.h"
#include "../../Enum/AnimationID.h"
#include "../../Enum/AudioID.h"
#include "../../Enum/AudioGroupID.h"
#include "../../Enum/CollisionLayer.h"
#include "../../Enum/EffectID.h"
#include "../../Enum/MeshID.h"
#include "../../Enum/MessageID.h"
#include "../../Constant/GameObjectName.h"
#include "../../Component/Common/AttackColliderController.h"
#include "../../Component/Common/Damageable.h"
#include "../../Component/Common/Rotator.h"
#include "../../Component/StateMachine/StateBehavior.h"
#include "../../Component/StateMachine/AnimationInfo.h"
#include "../../Component/Player/State/PlayerMoveState.h"
#include "../../Component/Player/State/PlayerAttackState.h"
#include "../../Component/Player/State/PlayerRollingState.h"
#include "../../Component/Player/State/PlayerDamageState.h"
#include "../../Component/Player/State/PlayerDeadState.h"
#include "../../Component/Player/HitStop.h"

using namespace Glib;

namespace
{
    /* === コライダー関連 ===  */

    const Vector3 BODY_COLLIDER_CENTER{ 0.0f, 0.76f, 0.0f };
    constexpr float BODY_COLLIDER_HEIGHT{ 0.43f };
    constexpr float BODY_COLLIDER_RADIUS{ 0.34f };
    const Vector3 ATK_COLLIDER_ANGLES{ 1.2f, 7.0f, 342.0f };
    const Vector3 ATK_COLLIDER_POSITION{ 0.08f, -0.03f, 0.63f };
    const Vector3 ATK_COLLIDER_SIZE{ 0.15f, 0.06f, 1.04f };

    /* === エフェクト関連 === */

    const Vector3 EFK_OFFSET_POSITION{ 0.0f, 0.0f, 0.6f };
    const Vector3 EFK_OFFSET_LOCALANGLES{ 90.0f, 0.0f, 0.0f };
    constexpr float EFK_PLAY_SPEED{ 5.0f };
    constexpr char ATK_COLLIDER_PARENT[]{ "Bip001 R Hand_WeaponBone" };

    /* === アニメーション関連 === */

    constexpr float ANIM_DEFAULT_BLEND_TIME{ 0.1f };

    /* === ヒットストップ === */

    constexpr unsigned int HITSTOP_MSG{ MessageID::Attacked };
    constexpr float HITSTOP_DURATION{ 0.1f };
    constexpr float HITSTOP_TIMESCALE{ 0.1f };
}

GameObjectPtr Player::Spawn()
{
    auto player = GameObjectManager::Instantiate(ObjectName::Player);
    auto playerAtk = GameObjectManager::Instantiate("PlayerATKCollider");
    auto playerEfk = GameObjectManager::Instantiate("PlayerSlashEffect");
    player->Layer(CollisionLayer::Player);
    playerAtk->Layer(CollisionLayer::PlayerAttack);

    SetMesh(player);
    SetDefaultAnimation(player);
    SetBodyCollider(player);
    SetAttackCollider(player, playerAtk);

    auto audio = player->AddComponent<AudioSource>();
    audio->SetGroup(AudioGroupID::SE);
    auto slashEfk = playerEfk->AddComponent<EffectSystem>();
    playerEfk->Transform()->Parent(playerAtk->Transform()->Parent());
    playerEfk->Transform()->LocalPosition(EFK_OFFSET_POSITION);
    playerEfk->Transform()->LocalEulerAngles(EFK_OFFSET_LOCALANGLES);
    slashEfk->EffectID(EffectID::SwordSwing);
    slashEfk->Speed(EFK_PLAY_SPEED);

    player->AddComponent<Rotator>();
    player->AddComponent<Damageable>(100, 100, 5, PlayerState::Damage, PlayerState::Dead);
    auto stateBehavior = player->AddComponent<StateBehavior>();

    PlayerMoveState::Parameter move{
        AnimationInfo{ AnimationID::PlayerIdle, 0.0f, ANIM_DEFAULT_BLEND_TIME, true },
        AnimationInfo{ AnimationID::PlayerMove, 0.0f, ANIM_DEFAULT_BLEND_TIME, true },
        4.0f,
        20.0f,
    };

    auto playerMove = player->AddComponent<PlayerMoveState>(move);
    playerMove->SetAnimationInfo(AnimationInfo{ AnimationID::PlayerIdle, 0.0f, ANIM_DEFAULT_BLEND_TIME, true });
    stateBehavior->AddState(playerMove, PlayerState::Moving);

    // 攻撃１
    PlayerAttackState::Parameter attack1{
        PlayerState::Attack2,
        AudioID::PlayerSwing,
        5,
        ValidityTimer{ 0.25f, 0.15f },
        0.09f,
        5.0f,
        20.0f,
        ValidityTimer{ 0.3f, 0.2f },
        0.1f,
    };
    auto playerAtk1 = player->AddComponent<PlayerAttackState>(attack1, slashEfk);
    playerAtk1->SetAnimationInfo(AnimationInfo{ AnimationID::PlayerAttack1 });
    stateBehavior->AddState(playerAtk1, PlayerState::Attack1);

    // 攻撃２
    PlayerAttackState::Parameter attack2{
        PlayerState::Attack3,
        AudioID::PlayerSwing,
        5,
        ValidityTimer{ 0.3f, 0.1f },
        0.2f,
        3.0f,
        20.0f,
        ValidityTimer{ 0.2f, 0.4f },
        0.1f,
    };
    auto playerAtk2 = player->AddComponent<PlayerAttackState>(attack2, slashEfk);
    playerAtk2->SetAnimationInfo(AnimationInfo{ AnimationID::PlayerAttack2 });
    stateBehavior->AddState(playerAtk2, PlayerState::Attack2);

    // 攻撃３
    PlayerAttackState::Parameter attack3{
        PlayerState::Attack4,
        AudioID::PlayerSwing,
        5,
        ValidityTimer{ 0.4f, 0.25f },
        0.125f,
        7.0f,
        20.0f,
        ValidityTimer{ 0.3f, 0.5f },
        0.1f,
    };
    auto playerAtk3 = player->AddComponent<PlayerAttackState>(attack3, slashEfk);
    playerAtk3->SetAnimationInfo(AnimationInfo{ AnimationID::PlayerAttack3 });
    stateBehavior->AddState(playerAtk3, PlayerState::Attack3);

    // 攻撃４
    PlayerAttackState::Parameter attack4{
        PlayerState::Moving,
        AudioID::PlayerSwing,
        5,
        ValidityTimer{ 0.7f },
        0.2f,
        5.0f,
        20.0f,
        ValidityTimer{ 0.0f, 0.0f },
        0.8f,
    };
    auto playerAtk4 = player->AddComponent<PlayerAttackState>(attack4, slashEfk);
    playerAtk4->SetAnimationInfo(AnimationInfo{ AnimationID::PlayerAttack4 });
    stateBehavior->AddState(playerAtk4, PlayerState::Attack4);

    // 回避
    PlayerRollingState::Parameter rolling{
        0.5f,
        ValidityTimer{ 0.4f, 0.05f },
        6.0f,
        20.0f,
    };
    auto playerRolling = player->AddComponent<PlayerRollingState>(rolling);
    playerRolling->SetAnimationInfo(AnimationInfo{ AnimationID::PlayerRolling });
    stateBehavior->AddState(playerRolling, PlayerState::Rolling);

    // ダメージ
    PlayerDamageState::Parameter damage{
        0.2f,
        3.0f,
        20.0f,
    };
    auto playerDamage = player->AddComponent<PlayerDamageState>(damage);
    playerDamage->SetAnimationInfo(AnimationInfo{ AnimationID::PlayerDamage });
    stateBehavior->AddState(playerDamage, PlayerState::Damage);

    // 死亡
    auto playerDead = player->AddComponent<PlayerDeadState>();
    playerDead->SetAnimationInfo(AnimationInfo{ AnimationID::PlayerDeath });
    stateBehavior->AddState(playerDead, PlayerState::Dead);

    return player;
}

void Player::SetMesh(const GameObjectPtr& player)
{
    auto renderer = player->AddComponent<SkinnedMeshRenderer>();
    renderer->MeshID(MeshID::Player);
}

void Player::SetDefaultAnimation(const GameObjectPtr& player)
{
    auto animator = player->AddComponent<Animator>();
    animator->AnimationID(AnimationID::PlayerIdle);
    animator->Loop(true);
}

void Player::SetBodyCollider(const GameObjectPtr& player)
{
    auto rigidbody = player->AddComponent<Rigidbody>();
    rigidbody->Constraints(RigidbodyConstraints::FreezeRotation);

    auto collider = player->AddComponent<CapsuleCollider>();
    collider->Center(BODY_COLLIDER_CENTER);
    collider->Height(BODY_COLLIDER_HEIGHT);
    collider->Radius(BODY_COLLIDER_RADIUS);
}

void Player::SetAttackCollider(const GameObjectPtr& player, const GameObjectPtr& collider)
{
    auto parent = player->Transform()->Find(ATK_COLLIDER_PARENT);
    auto rb = collider->AddComponent<Rigidbody>();
    auto boxCol = collider->AddComponent<BoxCollider>();
    collider->Transform()->Parent(parent);
    collider->Transform()->LocalPosition(ATK_COLLIDER_POSITION);
    collider->Transform()->LocalEulerAngles(ATK_COLLIDER_ANGLES);
    auto controller = collider->AddComponent<AttackColliderController>(boxCol);
    rb->IsKinematic(true);
    boxCol->IsTrigger(true);
    boxCol->Size(ATK_COLLIDER_SIZE);
    collider->AddComponent<HitStop>(HITSTOP_MSG, HITSTOP_DURATION, HITSTOP_TIMESCALE);
}
