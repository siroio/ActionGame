#pragma once
#include <WeakPtr.h>
#include "../../StateMachine/State.h"

namespace Glib
{
    class Animator;
}

struct Vector3;

/**
 * @brief プレイヤーダメージステート
 */
class PlayerIdleState : public State
{
public:
    PlayerIdleState(unsigned int nextState, float duration = 0.0f);
    void OnInitialize() override;
    int OnUpdate(float elapsedTime) override;

private:
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Animator> animator_{};
    float duration_{ 0.0f };
    int nextState_{ -1 };
};
