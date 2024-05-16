#include "Damageable.h"
#include <GameObject.h>
#include <Mathf.h>

#include "../StateMachine/StateBehavior.h"
#include <Debugger.h>
#include <GLGUI.h>

using namespace Glib;

Damageable::Damageable(int health, int maxHealth, int poise, int damageStateID, int deadStateID) :
    health_{ health }, maxHealth_{ maxHealth }, poise_{ poise },
    damageStateID_{ damageStateID }, deadStateID_{ deadStateID }
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
    return health_ > 0.0f ? static_cast<float>(health_) / maxHealth_ : 0.0f;
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
    // マイナス値の攻撃を与えられないようにMaxで0に丸める
    health_ -= Mathf::Max(power, 0);
    Debug::Log(GameObject()->Name() + ": HP :" + std::to_string(Health()));
    // ステートマシンを持っている場合
    // 死亡かダメージのステートへ推移
    if (power >= poise_) stateBehavior_->ChangeState(damageStateID_);
    if (IsDead()) stateBehavior_->ChangeState(deadStateID_);
    return true;
}

void Damageable::OnGUI()
{
    GLGUI::InputInt("MaxHealth", &maxHealth_);
    GLGUI::InputInt("Health", &health_);
    GLGUI::InputInt("Poise", &poise_);
    GLGUI::CheckBox("Invincible", &invincible_);
}
