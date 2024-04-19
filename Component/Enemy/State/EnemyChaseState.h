#pragma once
#include "../../StateMachine/State.h"

namespace Glib
{
    class Rigidbody;
}

struct Vector3;
class CharacterSearcher;
class Rotator;

class EnemyChaseState : public State
{
public:
    struct Parameter
    {
        int nextStateID{ -1 };
        float completeDistance{ 0.2f };
        float moveSpeed{ 4.0f };
        float moveForceMultiplier{ 20.0f };
    };

public:
    void OnInitialize() override;
    int OnFixedUpdate(float eplasedTime) override;

private:
    void Move();
    bool CompleteMove();
    Vector3 ToTargetDistance();
    Vector3 MoveSpeed(const Vector3& direction);

private:
    Glib::WeakPtr<Glib::Rigidbody> rigibody_{};
    Glib::WeakPtr<CharacterSearcher> searcher_{};
    Glib::WeakPtr<Rotator> rotator_{};
    Parameter parameter_{};
};
