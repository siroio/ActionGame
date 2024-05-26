#pragma once
#include <Component.h>

class CameraController;
class PlayerInput;

class CameraRotator : public Component
{
public:
    void Start();
    void FixedUpdate();

private:
    void Rotate();
    void OnGUI() override;

private:
    Glib::WeakPtr<CameraController> controller_{};
    Glib::WeakPtr<PlayerInput> input_{};
    float rotateSpeed_{ 130.0f };
    float interpolateRate{ 5.0f };
    float angleLimitPositiveX{ 50.0f };
    float angleLimitNegativeX{ -70.0f };
};
