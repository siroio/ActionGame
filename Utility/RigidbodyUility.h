#pragma once

namespace Glib
{
    template<class T>
    class WeakPtr;

    class Rigidbody;
}

struct RigidbodyUtility
{
    static void KillVelocity(const Glib::WeakPtr<Glib::Rigidbody>& rigidbody);
    static void KillXVelocity(const Glib::WeakPtr<Glib::Rigidbody>& rigidbody);
    static void KillYVelocity(const Glib::WeakPtr<Glib::Rigidbody>& rigidbody);
    static void KillZVelocity(const Glib::WeakPtr<Glib::Rigidbody>& rigidbody);
    static void KillXZVelocity(const Glib::WeakPtr<Glib::Rigidbody>& rigidbody);
};
