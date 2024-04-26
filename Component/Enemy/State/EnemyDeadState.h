#pragma once
#include "../../StateMachine/State.h"

class EnemyDeadState : public State
{
public:
    EnemyDeadState(float duration);

public:
    void OnEnter() override;
    int OnUpdate(float elapsedTime) override;

private:
    float duration_{ 0.0f };
};
