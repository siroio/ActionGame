#pragma once
#include "../../StateMachine/State.h"

namespace Glib
{
    class Rigidbody;
}

struct Vector3;

class EnemyDamageState : public State
{
public:
    struct Parameter
    {
        int nextStateID{ -1 };
        float duration{ 0.0f };
        float moveSpeed{ 5.0f };
        float moveForceMultiplier{ 20.0f };
    };

public:
    EnemyDamageState(const Parameter& parameter);

public:
    void OnInitialize() override;
    void OnEnter() override;
    int OnUpdate(float elapsedTime) override;
    int OnFixedUpdate(float elapsedTime) override;

private:
    void Move();
    Vector3 GetFlinchVelocity() const;
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    Parameter parameter_;
};
