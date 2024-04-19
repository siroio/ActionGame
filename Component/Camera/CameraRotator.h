#pragma once
#include <Component.h>
#include <WeakPtr.h>

namespace Glib
{
    class Transform;
}

class CameraController;

class CameraRotator : public Component
{
public:
    void Start();
    void FixedUpdate();

private:
    void Rotate();
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Transform> camera_{};
    Glib::WeakPtr<CameraController> controller_{};
    float rotateSpeed_{ 130.0f };
    float interpolateRate{ 5.0f };
    float angleLimitPositiveX{ 50.0f };
    float angleLimitNegativeX{ -70.0f };
};
