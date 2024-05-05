#pragma once
#include <WeakPtr.h>
#include "../../StateMachine/State.h"

namespace Glib
{
    class Animator;
}

class PlayerDeadState : public State
{
private:
    void OnEnter() override;
};
