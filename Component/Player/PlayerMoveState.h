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
private:
    void OnEnter() override;
    void OnInitialize() override;
    int OnUpdate(float elapsedTime) override;
    int OnFixedUpdate(float elapsedTime) override;
    void Move();
    void ChangeAnimation(unsigned int ID);
    void OnGUI() override;

private:
    Vector3 moveInput_{ Vector3::Zero() };
    float moveSpeed_{ 4.0f };
    float moveForceMultiplier_{ 20.0f };
    Glib::WeakPtr<Glib::Transform> camera_;
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_;
    Glib::WeakPtr<Glib::Animator> animator_;
    Glib::WeakPtr<Rotator> rotator_;
};
