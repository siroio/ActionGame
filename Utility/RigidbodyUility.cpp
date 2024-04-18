#include "RigidbodyUility.h"
#include <WeakPtr.h>
#include <Components/Rigidbody.h>
#include <Vector3.h>

namespace
{
    const Vector3 XVECTOR{ 0.0f, 1.0f, 1.0f };
    const Vector3 YVECTOR{ 1.0f, 0.0f, 1.0f };
    const Vector3 ZVECTOR{ 1.0f, 1.0f, 0.0f };
    const Vector3 XZVECTOR{ 0.0f, 1.0f, 0.0f };
}

void RigidbodyUtility::KillVelocity(const RigidbodyPtr& rigidbody)
{
    rigidbody->LinearVelocity(Vector3::Zero());
}

void RigidbodyUtility::KillXVelocity(const RigidbodyPtr& rigidbody)
{
    rigidbody->LinearVelocity(Vector3::Scale(rigidbody->LinearVelocity(), XVECTOR));
}

void RigidbodyUtility::KillYVelocity(const RigidbodyPtr& rigidbody)
{
    rigidbody->LinearVelocity(Vector3::Scale(rigidbody->LinearVelocity(), YVECTOR));
}

void RigidbodyUtility::KillZVelocity(const RigidbodyPtr& rigidbody)
{
    rigidbody->LinearVelocity(Vector3::Scale(rigidbody->LinearVelocity(), ZVECTOR));
}

void RigidbodyUtility::KillXZVelocity(const RigidbodyPtr& rigidbody)
{
    rigidbody->LinearVelocity(Vector3::Scale(rigidbody->LinearVelocity(), XZVECTOR));
}

Vector3 RigidbodyUtility::GetMoveVelocity(const RigidbodyPtr& rigidbody, const float moveForceMultiplier, const Vector3& moveSpeed)
{
    // y軸方向を無視して重力を無効化しないようにする
    Vector3 ignoreYVelocity = rigidbody->LinearVelocity();
    ignoreYVelocity.y = 0.0f;
    return moveForceMultiplier * (moveSpeed - ignoreYVelocity);
}
