#pragma once
#include <WeakPtr.h>
#include "../../StateMachine/State.h"
#include "../../../Utility/ValidityTimer.h"

namespace Glib
{
    class Animator;
    class AudioSource;
    class Rigidbody;
    class Transform;
}

class Rotator;
class PlayerInput;
class Damageable;

/**
 * @brief プレイヤー回避ステート
 */
class PlayerRollingState : public State
{
public:
    struct Parameter
    {
        // 回避パラメータ

        float dodgeDuration{ 0.0f };

        ValidityTimer invincibleTimer{ 0.0f, 0.0f };

        // 移動パラメータ
        float moveSpeed{ 4.0f };
        float moveForceMultiplier{ 20.0f };
    };

public:
    PlayerRollingState(const Parameter& parameter);

private:
    void OnInitialize() override;
    void OnEnter() override;
    int OnFixedUpdate(float elapsedTime) override;

private:
    void Move(bool moving);
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Transform> camera_{};
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    Glib::WeakPtr<Glib::AudioSource> audio_{};
    Glib::WeakPtr<Rotator> rotator_{};
    Glib::WeakPtr<PlayerInput> input_{};
    Glib::WeakPtr<Damageable> damageable_{};
    Parameter parameter_;
};
