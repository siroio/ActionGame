#pragma once
#include <Component.h>
namespace Glib
{
    class Transform;
}

class CharacterSearcher : public Component
{
public:
    float Fov() const;
    void Fov(float fov);
    bool TargetInFov(const Glib::WeakPtr<Glib::Transform>& target) const;

private:
    void OnGUI() override;

private:
    float fov_{ 0.0f };
};
