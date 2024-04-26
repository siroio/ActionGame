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
    if (stateIDs_.size() <= 0) return;

    // TODO: Fuzzy理論使いたい
    const int idx = Glib::Random::Range(0, static_cast<int>(stateIDs_.size()));
    stateBehavior_->ChangeState(stateIDs_.at(idx));
}

void EnemySelectorState::AddNextState(unsigned int id)
{
    stateIDs_.push_front(id);
}
