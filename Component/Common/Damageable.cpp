#include "Damageable.h"
#include <GameObject.h>
#include <Mathf.h>

#include "../StateMachine/StateBehavior.h"

Damageable::Damageable(int health, int maxHealth, int damageStateID, int deadStateID) :
    health_{ health }, maxHealth_{ maxHealth }, damageStateID_{ damageStateID }, deadStateID_{ deadStateID }
{}

void Damageable::Start()
{
    stateBehavior_ = GameObject()->GetComponent<StateBehavior>();
}

int Damageable::Health() const
{
    return health_;
}

void Damageable::Health(int add)
{
    health_ = Mathf::Clamp(health_ + add, 0, maxHealth_);
}

float Damageable::HealthRate() const
{
    return health_ <= 0.0f ? 0.0f : health_ / maxHealth_;
}

bool Damageable::Invincible() const
{
    return invincible_;
}

void Damageable::Invincible(bool enable)
{
    invincible_ = enable;
}

bool Damageable::IsDead() const
{
    return health_ <= 0;
}

bool Damageable::TakeDamage(int power)
{
    if (invincible_ || IsDead()) return false;

    // ダメージを与える
    // マイナス値の攻撃を与えられないようにMinで0に丸める
    health_ -= Mathf::Min(power, 0);

    // ステートマシンを持っている場合
    // 死亡かダメージのステートへ推移
    if (!stateBehavior_.expired()) return true;
    if (poise_ >= power) return true;
    stateBehavior_->ChangeState(IsDead() ? deadStateID_ : damageStateID_);

    return true;
}
