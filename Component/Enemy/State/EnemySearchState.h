#pragma once
#include "../../StateMachine/State.h"

namespace Glib
{
    class Transform;
}

class CharacterSearcher;
class Damageable;

/**
 * @brief 敵の探索ステート
 */
class EnemySearchState : public State
{
public:
    EnemySearchState(float searchCoolDown = 0.0f);
    void OnInitialize() override;
    int OnUpdate(float elapsedTime) override;

private:
    bool OnSearch();

private:
    Glib::WeakPtr<CharacterSearcher> searcher_{};
    float searchCoolDown_{};
};
