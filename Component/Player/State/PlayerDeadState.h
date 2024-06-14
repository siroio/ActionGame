#pragma once
#include <WeakPtr.h>
#include "../../StateMachine/State.h"

namespace Glib
{
    class Animator;
}

/**
 * @brief プレイヤー死亡ステート
 */
class PlayerDeadState : public State
{
private:
    void OnEnter() override;
};
