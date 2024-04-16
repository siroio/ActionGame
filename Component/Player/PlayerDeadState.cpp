#include "PlayerDeadState.h"
#include <GameObject.h>
#include <Components/Animator.h>

#include "../../Enum/AnimationID.h"

void PlayerDeadState::OnInitialize()
{
    animator_ = GameObject()->GetComponent<Glib::Animator>();
}

void PlayerDeadState::OnEnter()
{
    animator_->AnimationID(AnimationID::PlayerDeadth);
    animator_->Loop(true);
}
