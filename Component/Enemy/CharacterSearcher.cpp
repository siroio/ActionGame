#include "CharacterSearcher.h"
#include <Components/Transform.h>
#include <GameObject.h>
#include <Mathf.h>
#include <GLGUI.h>

float CharacterSearcher::Fov() const
{
    return fov_;
}

void CharacterSearcher::Fov(float fov)
{
    fov_ = Mathf::Min(Mathf::EPSILON, fov);
}

bool CharacterSearcher::TargetInFov(const Glib::WeakPtr<Glib::Transform>& target) const
{
    if (target.expired()) return false;
    const auto& transform = GameObject()->Transform();
    Vector3 forward = transform->Forward();
    Vector3 toTarget = target->Position() - transform->Position();
    forward.y = 0.0f;
    toTarget.y = 0.0f;
    return fov_ <= Vector3::Angle(forward, toTarget);
}

void CharacterSearcher::OnGUI()
{
    Glib::GLGUI::DragFloat("Fov", &fov_, 0.1f, 0.0f, 90.0f);
}
