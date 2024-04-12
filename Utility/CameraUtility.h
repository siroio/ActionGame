#pragma once
#include <WeakPtr.h>

namespace Glib
{
    class Transform;
}

struct Vector2;
struct Vector3;

struct CameraUtility
{
    /**
     * @brief Vector2の入力をカメラ視点からの入力へ変換
     * @param camera カメラ
     * @param input 入力
     * @return xzカメラ方向の入力
     */
    static Vector3 ConvertToCameraView(const Glib::WeakPtr<Glib::Transform>& camera, const Vector2& input);
};
