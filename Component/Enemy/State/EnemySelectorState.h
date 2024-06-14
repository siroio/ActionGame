#pragma once
#include "../../StateMachine/State.h"
#include <WeakPtr.h>
#include <deque>

class StateBehavior;

/**
 * @brief 敵の選択ステート
 */
class EnemySelectorState : public State
{
public:
    void OnInitialize() override;
    void OnEnter() override;
    void AddNextState(unsigned int id);

private:
    Glib::WeakPtr<StateBehavior> stateBehavior_{};
    std::deque<unsigned int> stateIDs_;
};
