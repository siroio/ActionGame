#pragma once
#include <WeakPtr.h>
#include "../../StateMachine/State.h"
#include "../../Utility/ValidityTimer.h"

namespace Glib
{
    class Animator;
    class Rigidbody;
}

class AttackColliderController;

class EnemyAttackState : public State
{
public:
    struct Parameter
    {
        int nextStateID{ -1 };
        int power{ 0 };
        float duration{ 0.0f };
        ValidityTimer attackTime{ 0.0f, 0.0f };
    };

public:
    EnemyAttackState(const Parameter& parameter);
    void OnInitialize() override;
    void OnEnter() override;
    int OnUpdate(float elapsedTime) override;
    void OnExit() override;

private:
    void OnGUI() override;

private:
    Glib::WeakPtr<AttackColliderController> attackCollider_{};
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    Parameter parameter_{};
};
