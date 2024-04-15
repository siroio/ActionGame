#pragma once
#include <Component.h>
#include <GameObjectPtr.h>

namespace Glib
{
    class Collider;
}

class AttackColliderController : public Component
{
public:
    AttackColliderController(const Glib::WeakPtr<Glib::Collider>& collider);

    /**
     * @brief 攻撃判定の有効切り替え
     * @param enable 有効
     */
    void SetAttackActive(bool enable);

    /**
     * @brief 威力の設定
     * @param power
     */
    void SetAttackPower(int power);

    void OnTriggerEnter(const GameObjectPtr& other);

private:
    Glib::WeakPtr<Glib::Collider> collider_;
    float power_{ 0.0f };
};
