#pragma once
#include "../Common/Rotator.h"
#include "../StateMachine/State.h"
#include <WeakPtr.h>
#include <Quaternion.h>

struct Vector3;

namespace Glib
{
    class Transform;
    class Rigidbody;
    class Animator;
}

class PlayerMoveState : public State
{
public:
    struct Parameter
    {
        AnimationInfo idleInfo{};
        AnimationInfo walkInfo{};
        float moveSpeed{ 4.0f };
        float moveForceMultiplier{ 20.0f };
    };

public:
    PlayerMoveState(const Parameter& parameter);

private:
    void OnInitialize() override;
    int OnUpdate(float elapsedTime) override;
    int OnFixedUpdate(float elapsedTime) override;
    void Move();
    void ChangeAnimation(bool moving);
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Transform> camera_{};
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    Glib::WeakPtr<Glib::Animator> animator_{};
    Glib::WeakPtr<Rotator> rotator_;
    Vector3 moveInput_{ Vector3::Zero() };
    Parameter parameter_;
};
