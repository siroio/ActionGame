#include "Projectile.h"
#include <Components/Rigidbody.h>
#include <GameObject.h>
#include <GameTimer.h>
#include <GLGUI.h>

using namespace Glib;

void Projectile::Start()
{
    rigidbody_ = GameObject()->GetComponent<Rigidbody>();
}

void Projectile::FixedUpdate()
{
    if (rigidbody_.expired()) return;
    Move();
}

float Projectile::MoveSpeed() const
{
    return moveSpeed_;
}

void Projectile::MoveSpeed(float speed)
{
    moveSpeed_ = speed;
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
}
