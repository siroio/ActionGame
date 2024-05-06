#pragma once
#include <Component.h>

namespace Glib
{
    class Transform;
    class Rigidbody;
}

class Projectile : public Component
{
public:
    Projectile(const Glib::WeakPtr<Glib::Transform>& target);
    void Start();
    void FixedUpdate();

    float MoveSpeed() const;
    void MoveSpeed(float speed);
    float RotateSpeed() const;
    void RotateSpeed(float speed);

private:
    void Rotation();
    void Move();
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Rigidbody> rigidbody_{};
    Glib::WeakPtr<Glib::Transform> target_{};
    float moveSpeed_{ 10.0f };
    float rotateSpeed_{ 5.0f };
};
