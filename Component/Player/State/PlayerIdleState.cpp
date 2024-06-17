#include "PlayerIdleState.h"
#include <GameObject.h>
#include <Components/Animator.h>
#include <GLGUI.h>

#include "../../Enum/State/PlayerState.h"
#include "PlayerIdleState.h"

using namespace Glib;

PlayerIdleState::PlayerIdleState(unsigned int nextState, float duration) :
    nextState_{ static_cast<int>(nextState) }, duration_{ duration }
{}

void PlayerIdleState::OnInitialize()
{
    animator_ = GameObject()->GetComponent<Animator>();
}

int PlayerIdleState::OnUpdate(float elapsedTime)
{
    if (elapsedTime >= duration_)
    {
        return nextState_;
    }
    return STATE_MAINTAIN;
}

void PlayerIdleState::OnGUI()
{
    GLGUI::InputInt("NextState", &nextState_);
    GLGUI::DragFloat("Duration", &duration_, 0.1f);
}
