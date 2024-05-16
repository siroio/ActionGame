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

    /**
     * @brief 回転が終了したのか
     */
    bool IsCompleteRotate() const;
    void Direction(const Vector3& direction);
    const Vector3& Direction() const;

private:
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Transform> transform_;
    Vector3 direction_{ Vector3::Forward() };
    float turnSpeed_{ 15.0f };
};
