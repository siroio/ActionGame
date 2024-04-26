#pragma once
#include <Component.h>
#include <unordered_map>

namespace Glib
{
    class Animator;
}

class State;

class StateBehavior : public Component
{
public:
    void Start();
    void FixedUpdate();
    void Update();
    void LateUpdate();
    void AddState(const Glib::WeakPtr<State>& state, unsigned int stateID);
    void ChangeState(unsigned int stateID);

private:
    void OnGUI() override;

private:
    float elapsedTime{ 0.0f };
    float elapsedFixedTime{ 0.0f };
    unsigned int startStateID_{ 0U };
    Glib::WeakPtr<State> currentState_{};
    Glib::WeakPtr<Glib::Animator> animator_{};
    std::unordered_map<unsigned int, Glib::WeakPtr<State>> stateList_;
};
