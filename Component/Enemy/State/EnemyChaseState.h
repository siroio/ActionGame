#pragma once
#include "../../StateMachine/State.h"
#include <vector>

namespace Glib
{
    class Rigidbody;
}

struct Vector3;
class CharacterSearcher;
class Rotator;

/**
 * @brief 敵の追いかけステート
 */
class EnemyChaseState : public State
{
public:
    struct Parameter
    {
        float completeDistance{ 0.2f };
        float moveSpeed{ 4.0f };
        float moveForceMultiplier{ 20.0f };
    };

public:
    EnemyChaseState(const Parameter& parameter);
    void AddNextState(unsigned int id);
    void OnInitialize() override;
    int OnUpdate(float) override;
    int OnFixedUpdate(float) override;

private:
    void Move();
    bool CompleteMove();
    Vector3 ToTargetDistance();
    Vector3 MoveSpeed(const Vector3& direction);

private:
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Rigidbody> rigibody_{};
    Glib::WeakPtr<CharacterSearcher> searcher_{};
    Glib::WeakPtr<Rotator> rotator_{};
    std::vector<unsigned int> stateIDs_;
    Parameter parameter_{};
};
