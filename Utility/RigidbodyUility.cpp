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

void RigidbodyUtility::KillVelocity(const Glib::WeakPtr<Glib::Rigidbody>& rigidbody)
{
    rigidbody->LinearVelocity(Vector3::Zero());
}

void RigidbodyUtility::KillXVelocity(const Glib::WeakPtr<Glib::Rigidbody>& rigidbody)
{
    rigidbody->LinearVelocity(Vector3::Scale(rigidbody->LinearVelocity(), XVECTOR));
}

void RigidbodyUtility::KillYVelocity(const Glib::WeakPtr<Glib::Rigidbody>& rigidbody)
{
    rigidbody->LinearVelocity(Vector3::Scale(rigidbody->LinearVelocity(), YVECTOR));
}

void RigidbodyUtility::KillZVelocity(const Glib::WeakPtr<Glib::Rigidbody>& rigidbody)
{
    rigidbody->LinearVelocity(Vector3::Scale(rigidbody->LinearVelocity(), ZVECTOR));
}

void RigidbodyUtility::KillXZVelocity(const Glib::WeakPtr<Glib::Rigidbody>& rigidbody)
{
    rigidbody->LinearVelocity(Vector3::Scale(rigidbody->LinearVelocity(), XZVECTOR));
}
