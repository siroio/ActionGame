#pragma once
#include <Component.h>
#include "AnimationInfo.h"

namespace Glib
{
    template<class T>
    class WeakPtr;

    class Animator;
}

class State : public Component
{
public:
    static constexpr int STATE_MAINTAIN{ -1 };

    State() = default;
    virtual ~State() = default;

    virtual void OnInitialize()
    {}
    virtual void OnEnter()
    {}
    virtual int OnFixedUpdate(float elapedTime)
    {
        return STATE_MAINTAIN;
    }
    virtual int OnUpdate(float elapedTime)
    {
        return STATE_MAINTAIN;
    }
    virtual int OnLateUpdate(float elapedTime)
    {
        return STATE_MAINTAIN;
    }
    virtual void OnExit()
    {}

    void SetAnimationInfo(const AnimationInfo& info);
    void SetAnimation(Glib::WeakPtr<Glib::Animator>& animator) const;

private:
    AnimationInfo animationInfo_{};
};
