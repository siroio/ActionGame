#pragma once
#include <WeakPtr.h>
#include <Component.h>
#include <Components/Transform.h>
#include <Vector3.h>

class CameraController : public Component
{
public:
    struct Parameter
    {
    public:
        Vector3 Position{ Vector3::Zero() };
        Vector3 Angle{ Vector3::Zero() };
        Vector3 Offset{ Vector3::Zero() };
        Vector3 OffsetAngle{ Vector3::Zero() };
        float Distance{ 0.0f };
        float FollowSpeed{ 5.0f };
        float RotateSpeed{ 5.0f };
        bool ObstacleDetection{ true };
        Glib::WeakPtr<Glib::Transform> Target{};
    };

public:
    static Vector3 LerpAngle(const Vector3& a, const Vector3& b, float t);
    static Parameter Lerp(const Parameter& a, const Parameter& b, float t);

public:
    CameraController(const Parameter& parameter);
    void Start();
    void FixedUpdate();
    void SetTarget(const Glib::WeakPtr<Glib::Transform>& target);
    Parameter GetParameter() const;
    void SetParameter(const Parameter& parameter);

private:
    void ObstacleDetection();
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Transform> parent_{};
    Glib::WeakPtr<Glib::Transform> child_{};
    Glib::WeakPtr<Glib::Transform> camera_{};

private:
    Parameter parameter_{};
};
