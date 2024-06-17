#pragma once
#include <Component.h>

class Damageable;

/**
 * @brief キャラの死亡を監視するコンポーネント
 */
class PlayerDeadObserver : public Component
{
public:
    void Start();
    void Update();

private:
    Glib::WeakPtr<Damageable> damageable_{};
};
