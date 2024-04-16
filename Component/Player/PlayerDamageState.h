#pragma once
#include <WeakPtr.h>
#include "../StateMachine/State.h"

namespace Glib
{
    class Animator;
    class AudioSource;
    class Rigidbody;
}

class Damageable;
struct Vector3;

class PlayerDamageState : public State
{
public:
    struct Parameter
    {
        // アニメーションパラメータ

        int damageAnimID{ -1 };

        // 長さ
        float damageDuration{ 0.0f };

        // 移動パラメータ
        float moveSpeed{ 5.0f };
        float moveForceMultiplier{ 20.0f };
    };

public:
    PlayerDamageState(const Parameter& parameter);

private:
    void OnInitialize() override;
    void OnEnter() override;
    int OnUpdate(float elapsedTime) override;
    int OnFixedUpdate(float elapsedTime) override;

private:
    void Move(bool moving);
    Vector3 GetFlinchVelocity() const;
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    Glib::WeakPtr<Glib::Animator> animator_{};
    Glib::WeakPtr<Glib::AudioSource> audio_{};
    Parameter parameter_;
};
