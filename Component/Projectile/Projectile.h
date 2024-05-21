#pragma once
#include <Component.h>

namespace Glib
{
    class Rigidbody;
}

class Projectile : public Component
{
public:
    void Start();
    void FixedUpdate();

    float MoveSpeed() const;
    void MoveSpeed(float speed);

private:
    void Move();
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    float moveSpeed_{ 10.0f };
};
