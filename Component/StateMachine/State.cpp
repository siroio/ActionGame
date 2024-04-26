#include "State.h"
#include "AnimationInfo.h"
#include <Components/Animator.h>

void State::SetAnimationInfo(const AnimationInfo& info)
{
    animationInfo_ = info;
}

void State::SetAnimation(Glib::WeakPtr<Glib::Animator>& animator) const
{
    if (animator.expired()) return;
    animator->AnimationID(animationInfo_.AnimationID, animationInfo_.FrameOffset);
    animator->BlendTime(animationInfo_.BlendTime);
    animator->Loop(animationInfo_.Loop);
}
