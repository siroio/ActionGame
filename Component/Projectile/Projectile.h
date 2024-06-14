#pragma once
#include <Component.h>

namespace Glib
{
    class Rigidbody;
}

/**
 * @brief 飛翔物コンポーネント
 */
class Projectile : public Component
{
public:
    void Start();
    void FixedUpdate();

    /**
     * @brief 移動速度の取得
     */
    float MoveSpeed() const;

    /**
     * @brief 移動速度の設定
     */
    void MoveSpeed(float speed);

private:
    void Move();
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    float moveSpeed_{ 10.0f };
};
