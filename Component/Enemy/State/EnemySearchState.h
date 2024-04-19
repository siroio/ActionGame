#pragma once
#include "../../StateMachine/State.h"

namespace Glib
{
    class Transform;
}

class CharacterSearcher;
class Damageable;

class EnemySearchState : public State
{
public:
    struct Parameter
    {
        float searchCoolDown;
    };

public:
    EnemySearchState(const Parameter& parameter);
    void OnInitialize() override;
    int OnUpdate(float elapsedTime) override;

private:
    bool OnSearch();

private:
    Glib::WeakPtr<CharacterSearcher> searcher_{};
    Parameter parameter_{};
};
