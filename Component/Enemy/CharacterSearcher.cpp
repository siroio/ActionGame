#include "CharacterSearcher.h"
#include <Components/Transform.h>
#include <GameObject.h>
#include <GLGUI.h>

CharacterSearcher::CharacterSearcher(float fov, float distance, GameObjectPtr target) :
    fov_{ fov }, distance_{ distance }, target_{ target }
{}

float CharacterSearcher::Distance() const
{
    return distance_;
}

void CharacterSearcher::Distance(float distance)
{
    distance_ = distance;
}

float CharacterSearcher::Fov() const
{
    return fov_;
}

void CharacterSearcher::Fov(float fov)
{
    fov_ = Mathf::Min(Mathf::EPSILON, fov);
}

GameObjectPtr CharacterSearcher::Target() const
{
    return target_;
}

void CharacterSearcher::Target(const GameObjectPtr& target)
{
    target_ = target;
}

bool CharacterSearcher::TargetInView() const
{
    if (target_.expired()) return false;
    const auto& transform = GameObject()->Transform();
    const auto& target = target_->Transform();
    Vector3 forward = transform->Forward();
    Vector3 toTarget = target->Position() - transform->Position();

    // 高さを無視する
    forward.y = 0.0f;
    toTarget.y = 0.0f;

    // 一定距離離れているか？
    if (toTarget.SqrMagnitude() > distance_ * distance_) return false;

    // fovの内側か？
    return fov_ <= Vector3::Angle(forward, toTarget.Normalized());
}

void CharacterSearcher::OnGUI()
{
    Glib::GLGUI::DragFloat("Fov", &fov_, 0.1f, 0.0f, 90.0f);
}
