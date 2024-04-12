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
    void Start();

    /**
     * @brief 攻撃判定の有効切り替え
     * @param enable 有効
     */
    void SetAttckActive(bool enable);
    void OnTriggerEnter(const GameObjectPtr& other);

private:
    Glib::WeakPtr<Glib::Collider> collider_;
};
