#pragma once
#include <WeakPtr.h>
#include "../StateMachine/State.h"

namespace Glib
{
    class Animator;
}

class PlayerDeadState : public State
{
public:
    void OnInitialize() override;
    void OnEnter();

private:
    Glib::WeakPtr<Glib::Animator> animator_{};
};
