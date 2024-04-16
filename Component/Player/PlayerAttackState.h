#pragma once
#include <WeakPtr.h>
#include "../StateMachine/State.h"
#include "../../Utility/ReceptionTimer.h"

namespace Glib
{
    class Animator;
    class AudioSource;
    class Rigidbody;
    class Transform;
    class EffectSystem;
}

struct Vector3;
class Rotator;

class PlayerAttackState : public State
{
public:
    /**
     * @brief 次のステートID
     * @brief アニメーションID
     * @brief ループするか
     * @brief 攻撃力
     * @brief 受付時間(時間, 受付開始までの時間)
     * @brief 受付終了後のステート変更の待機時間
     */
    struct Parameter
    {
        // 次の攻撃のID
        int nextAttackState{ -1 };

        // アニメーションパラメータ
        int attackAnimID{ -1 };
        bool isLoop{ false };

        // SEパラメータ
        int attackSEID{ -1 };

        // 攻撃のパラメータ
        int attack{ 0 };

        // 攻撃時移動用パラメータ
        float moveDuration{ 0.0f };
        float moveSpeed{ 4.0f };
        float moveForceMultiplier{ 20.0f };

        // 時間系のパラメータ
        ReceptionTimer inputTimer;
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
    bool IsAtacck(float elapsedTime);
    bool IsTimeOver(float elapsedTime) const;
    void Move(float elapsedTime);
    Vector3 MoveSpeed(bool moving);
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Transform> camera_{};
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    Glib::WeakPtr<Glib::Animator> animator_{};
    Glib::WeakPtr<Glib::AudioSource> audio_{};
    Glib::WeakPtr<Glib::EffectSystem> slashEfk_{};
    Glib::WeakPtr<Rotator> rotator_{};
    Parameter parameter_;
};
