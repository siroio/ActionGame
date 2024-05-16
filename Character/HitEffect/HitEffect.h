#pragma once
#include <GameObjectPtr.h>

struct Vector3;

struct HitEffect
{
    /**
     * @brief ヒットエフェクトの生成
     * @param position エフェクト位置
     * @return エフェクトオブジェクト
     */
    static GameObjectPtr Spawn(const Vector3& position);
};
