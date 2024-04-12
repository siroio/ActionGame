#pragma once
#include <Component.h>
#include <WeakPtr.h>
#include <Vector3.h>

namespace Glib
{
    class Transform;
}

class Rotator : public Component
{
public:
    void Start();
    void Update();
    void Direction(const Vector3& direction);
    const Vector3& Direction() const;

private:
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Transform> transform_;

    float turnSpeed_{ 15.0f };
    Vector3 direction_{ Vector3::Forward() };
};
