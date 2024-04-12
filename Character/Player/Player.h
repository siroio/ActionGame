#pragma once
#include <GameObjectPtr.h>

struct Player
{
    /**
     * @brief プレイヤーの生成
     * @return 生成できたか
     */
    static void Create();

private:
    static void SetMesh(const GameObjectPtr& player);
    static void SetDefaultAnimation(const GameObjectPtr& player);
    static void SetBodyCollider(const GameObjectPtr& player);
    static void SetAttackCollider(const GameObjectPtr& player, const GameObjectPtr& collider);
};
