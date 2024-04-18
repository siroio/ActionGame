#pragma once

namespace Glib
{
    template<class T>
    class WeakPtr;

    class Rigidbody;
}

struct Vector3;

struct RigidbodyUtility
{
private:
    using RigidbodyPtr = Glib::WeakPtr<Glib::Rigidbody>;

public:
    /**
     * @brief 移動速度をゼロにする
     * @param rigidbody
     */
    static void KillVelocity(const RigidbodyPtr& rigidbody);

    /**
     * @brief X軸方向の移動速度をゼロにする
     * @param rigidbody
     */
    static void KillXVelocity(const RigidbodyPtr& rigidbody);

    /**
     * @brief Y軸方向の移動速度をゼロにする
     * @param rigidbody
     */
    static void KillYVelocity(const RigidbodyPtr& rigidbody);

    /**
     * @brief Z軸方向の移動速度をゼロにする
     * @param rigidbody
     */
    static void KillZVelocity(const RigidbodyPtr& rigidbody);

    /**
     * @brief XZ軸方向の移動速度をゼロにする
     * @param rigidbody
     */
    static void KillXZVelocity(const RigidbodyPtr& rigidbody);

    /**
     * @brief Velocityに応じた速度を返す
     * @param rigidbody
     * @param moveForceMultiplier 変化倍率
     * @param moveSpeed 移動速度
     * @return 移動速度
     */
    static Vector3 GetMoveVelocity(const RigidbodyPtr& rigidbody, const float moveForceMultiplier, const Vector3& moveSpeed);
};
