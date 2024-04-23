#pragma once
#include <GameObjectPtr.h>
#include <Vector3.h>

struct MainCamera
{
    /**
     * @brief メインカメラの生成
     * @return 生成できたか
     */
    static GameObjectPtr Spawn(const Vector3& offset, const float distance);
};
