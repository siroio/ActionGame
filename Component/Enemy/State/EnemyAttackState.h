#pragma once
#include "../../StateMachine/State.h"
#include "../../Utility/ReceptionTimer.h"

namespace Glib
{
    class Animator;
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
        ReceptionTimer attackTime{ 0.0f, 0.0f };
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
    Parameter parameter_{};
};
