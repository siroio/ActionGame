#include "StateBehavior.h"
#include "State.h"
#include <Components/Animator.h>
#include <GameObject.h>
#include <GameTimer.h>
#include <StringUtility.h>
#include <Debugger.h>
#include <GLGUI.h>

using namespace Glib;

void StateBehavior::Start()
{
    if (currentState_.expired()) return;
    animator_ = GameObject()->GetComponent<Animator>();
    currentState_->SetAnimation(animator_);
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
    const auto& idStr = std::to_string(stateID);
    if (state.expired())
    {
        Debug::Error("ステートが見つかりません。 ID: " + idStr);
        return;
    }
    if (stateList_.contains(stateID))
    {
        Debug::Warn("追加された、ステートIDが重複しています。ID: " + idStr);
        Debug::Warn("重複したステートは上書きされます。");
    }
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
    currentState_->SetAnimation(animator_);
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
