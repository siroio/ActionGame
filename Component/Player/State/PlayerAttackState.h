#pragma once
#include <WeakPtr.h>
#include "../../StateMachine/State.h"
#include "../../../Utility/ValidityTimer.h"

namespace Glib
{
    class AudioSource;
    class Rigidbody;
    class Transform;
    class EffectSystem;
}

struct Vector3;
class Rotator;
class AttackColliderController;
class DelayedAudioPlayer;
class PlayerInput;

class PlayerAttackState : public State
{
public:
    /**
     * @brief 次のステートID
     * @brief 攻撃力
     * @brief 受付時間(時間, 受付開始までの時間)
     * @brief 受付終了後のステート変更の待機時間
     */
    struct Parameter
    {
        // 次の攻撃のID
        int nextAttackState{ -1 };

        // SEパラメータ
        int attackSEID{ -1 };

        // 攻撃のパラメータ
        int power{ 0 };

        ValidityTimer colliderTimer;

        // 攻撃時移動用パラメータ
        float moveDuration{ 0.0f };
        float moveSpeed{ 4.0f };
        float moveForceMultiplier{ 20.0f };

        // 時間系のパラメータ
        ValidityTimer inputTimer;
        float stateEndTime{ 0 };
    };

public:
    PlayerAttackState(const Parameter& parameter, const Glib::WeakPtr<Glib::EffectSystem>& context);

private:
    void OnInitialize() override;
    void OnEnter() override;
    void OnExit() override;
    int OnUpdate(float elapsedTime) override;
    int OnFixedUpdate(float elapsedTime) override;

    bool IsAttack(float elapsedTime);
    bool EnableAttack(float elapsedTime);
    bool IsTimeOver(float elapsedTime) const;
    void Move(float elapsedTime);
    Vector3 MoveSpeed(bool moving);
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Transform> camera_{};
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    Glib::WeakPtr<Glib::EffectSystem> slashEfk_{};
    Glib::WeakPtr<DelayedAudioPlayer> audio_{};
    Glib::WeakPtr<Rotator> rotator_{};
    Glib::WeakPtr<PlayerInput> input_{};
    Glib::WeakPtr<AttackColliderController> attackCollider_{};
    Parameter parameter_;
};
