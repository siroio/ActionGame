#pragma once
#include <Component.h>
#include <unordered_map>

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
    Glib::WeakPtr<State> currentState_{ nullptr };
    std::unordered_map<unsigned int, Glib::WeakPtr<State>> stateList_;
};
