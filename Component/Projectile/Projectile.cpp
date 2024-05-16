#include "Projectile.h"
#include <Components/Transform.h>
#include <Components/Rigidbody.h>
#include <GameObject.h>
#include <GameTimer.h>
#include <GLGUI.h>

#include "../../Common/Rotator.h"

using namespace Glib;

Projectile::Projectile(const Glib::WeakPtr<Glib::Transform>& target, float hitThreshold) :
    target_{ target }, hitThreshold_{ hitThreshold }
{}

void Projectile::Start()
{
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
    rotator_ = GameObject()->GetComponent<Rotator>();
}

void Projectile::FixedUpdate()
{
    if (!target_.expired() && isChase_)
    {
        // ターゲットの方向へ向ける
        Rotation();

        CheckHit();
    }

    if (!rigidbody_.expired())
    {
        // 移動させる
        Move();
    }
}

float Projectile::MoveSpeed() const
{
    return moveSpeed_;
}

void Projectile::MoveSpeed(float speed)
{
    moveSpeed_ = speed;
}

float Projectile::RotateSpeed() const
{
    return rotateSpeed_;
}

void Projectile::RotateSpeed(float speed)
{
    rotateSpeed_ = speed;
}

void Projectile::CheckHit()
{
    const float distance = (target_->Position() - GameObject()->Transform()->Position()).SqrMagnitude();
    if (distance <= hitThreshold_ * hitThreshold_)
    {
        isChase_ = false;
    }
}

void Projectile::Rotation()
{
    const auto& transform = GameObject()->Transform();
    Vector3 direction = (target_->Position() - transform->Position()).Normalized();
    rotator_->Direction(direction);
}

void Projectile::Move()
{
    Vector3 forward = GameObject()->Transform()->Forward();
    Vector3 velocity = forward * moveSpeed_;
    rigidbody_->LinearVelocity(velocity);
}

void Projectile::OnGUI()
{
    GLGUI::DragFloat("MoveSpeed", &moveSpeed_, 0.1f, 0.0f);
    GLGUI::DragFloat("RotationSpeed", &rotateSpeed_, 0.1f, 0.0f);
    GLGUI::DragFloat("HitThreshold", &hitThreshold_, 0.1f, 0.0f);
}
