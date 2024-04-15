#include "StateBehavior.h"
#include "State.h"
#include <StringUtility.h>
#include <GameTimer.h>
#include <string>
#include <GLGUI.h>

using namespace Glib;

void StateBehavior::Start()
{
    if (currentState_.expired()) return;
}

void StateBehavior::FixedUpdate()
{
    if (currentState_.expired()) return;
    int nextState = currentState_->OnFixedUpdate(elapsedFixedTime);
    elapsedFixedTime += GameTimer::FixedDeltaTime();
    if (nextState >= 0) ChangeState(nextState);
}

void StateBehavior::Update()
{
    if (currentState_.expired()) return;
    int nextState = currentState_->OnUpdate(elapsedTime);
    elapsedTime += GameTimer::DeltaTime();
    if (nextState >= 0) ChangeState(nextState);
}

void StateBehavior::LateUpdate()
{
    if (currentState_.expired()) return;
    int nextState = currentState_->OnLateUpdate(elapsedTime);
    if (nextState >= 0) ChangeState(nextState);
}

void StateBehavior::AddState(const WeakPtr<State>& state, unsigned int stateID)
{
    if (state.expired()) return;
    stateList_[stateID] = state;
    state->OnInitialize();
    if (currentState_.expired()) ChangeState(stateID);
}

void StateBehavior::ChangeState(unsigned int stateID)
{
    if (stateID < 0) return;
    const auto& state = stateList_.find(stateID);
    if (state == stateList_.end()) return;
    if (!currentState_.expired())
    {
        currentState_->OnExit();
    }
    currentState_ = state->second;
    currentState_->OnEnter();
    elapsedFixedTime = 0.0f;
    elapsedTime = 0.0f;
}

void StateBehavior::OnGUI()
{
    std::string currentState{ "Current State: " };
    currentState += currentState_.expired() ? "None" : nameof(*currentState_.get().get());
    GLGUI::Text(currentState);
}
