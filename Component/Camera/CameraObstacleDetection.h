#pragma once
#include <Component.h>

class CameraController;

class CameraObstacleDetection : public Component
{
public:
    void Start();
    void FixedUpdate();

private:
    void OnGUI() override;

private:
    Glib::WeakPtr<CameraController> controller_{};
    float offset_{ 0.2f };
};
