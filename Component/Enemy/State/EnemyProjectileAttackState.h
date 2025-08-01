﻿#pragma once
#include "../../StateMachine/State.h"
#include <GameObjectPtr.h>
#include <WeakPtr.h>
#include <functional>
#include <Vector3.h>

class StateBehavior;
class CharacterSearcher;

/**
 * @brief 敵の遠距離攻撃ステート
 */
class EnemyProjectileAttackState : public State
{
public:
    using SpawnFunction = std::function<void(const Vector3&, float, const GameObjectPtr&)>;

public:
    struct Parameter
    {
        int nextStateID{ -1 };
        SpawnFunction spawn{ nullptr };
        Vector3 spawnPoint{ 0.0f };
        float flySpeed{ 0.0f };
        float duration{ 0.0f };
        float delay{ 0.0f };
    };

public:
    EnemyProjectileAttackState(const Parameter& parameter);
    void OnEnter() override;
    void OnInitialize() override;
    int OnUpdate(float elapsedTime) override;

private:
    void Attack();

private:
    Glib::WeakPtr<StateBehavior> stateBehavior_{};
    Glib::WeakPtr<CharacterSearcher> searcher_{};
    Parameter parameter_;
    bool attacked_{ false };
};
