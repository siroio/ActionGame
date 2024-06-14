#pragma once
#include <WeakPtr.h>
#include <Component.h>

class StateBehavior;

/**
 * @brief ダメージオブジェクトコンポーネント
 */
class Damageable : public Component
{
public:
    Damageable(int health, int maxHealth, int poise, int damageStateID, int deadStateID);

    void Start();

    /**
     * @brief 残存体力
     */
    int Health() const;

    /**
     * @brief 体力の加算
     */
    void Health(int add);

    /**
     * @brief 体力の歩合を0~1で返す
     */
    float HealthRate() const;

    /**
     * @brief 攻撃が無効か？
     */
    bool Invincible() const;

    /**
     * @brief 攻撃を無効に設定
     * @param enable
     */
    void Invincible(bool enable);

    /**
     * @brief 死亡しているか？
     */
    bool IsDead() const;

    /**
     * @brief ダメージを与える
     * @param power 威力
     * @return
     */
    bool TakeDamage(int power);

private:
    void OnGUI() override;

private:
    int health_{ 0 };
    int maxHealth_{ 0 };
    int poise_{ 0 };
    int damageStateID_{ -1 };
    int deadStateID_{ -1 };
    bool invincible_{ false };
    Glib::WeakPtr<StateBehavior> stateBehavior_{};
};
