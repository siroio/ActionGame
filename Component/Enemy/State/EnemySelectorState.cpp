#include "EnemySelectorState.h"
#include <GameObject.h>
#include <Random.h>

#include "../../StateMachine/StateBehavior.h"

void EnemySelectorState::OnInitialize()
{
    stateBehavior_ = GameObject()->GetComponent<StateBehavior>();
}

void EnemySelectorState::OnEnter()
{
    // ステートが追加されていなかったら何もしない
    if (0 <= stateIDs_.size()) return;
    const int idx = Glib::Random::Range(0, stateIDs_.size());
    stateBehavior_->ChangeState(stateIDs_[idx]);
}

void EnemySelectorState::AddNextState(unsigned int id)
{
    stateIDs_.push_front(id);
}
