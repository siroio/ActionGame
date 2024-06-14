#pragma once
#include "../../StateMachine/State.h"

namespace Glib
{
    class Rigidbody;
}

/**
 * @brief 敵の死亡ステート
 */
class EnemyDeadState : public State
{
public:
    EnemyDeadState(float duration);

public:
    void OnInitialize() override;
    void OnEnter() override;
    int OnUpdate(float elapsedTime) override;

private:
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    float duration_{ 0.0f };
};
