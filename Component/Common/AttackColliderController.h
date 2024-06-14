#pragma once
#include <Component.h>
#include <GameObjectPtr.h>
#include <vector>

namespace Glib
{
    class Collider;
}

/**
 * @brief 攻撃制御ようコンポーネント
 */
class AttackColliderController : public Component
{
public:
    AttackColliderController(bool onHitDestroy = false);

    /**
     * @brief 判定の追加
     * @param collider
     */
    void AddCollider(const Glib::WeakPtr<Glib::Collider>& collider);

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

    /**
     * @brief 攻撃したとき
     * @param other 相手
     */
    void OnTriggerEnter(const GameObjectPtr& other);

private:
    std::vector<Glib::WeakPtr<Glib::Collider>> colliders_;
    int power_{ 0 };
    bool onHitDestroy_{ false };
};
