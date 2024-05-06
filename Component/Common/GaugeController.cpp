#include "GaugeController.h"
#include <Components/Transform.h>
#include <Components/Image.h>
#include <GameObject.h>
#include <GameTimer.h>
#include <Mathf.h>
#include <GLGUI.h>

#include "Damageable.h"

using namespace Glib;

GaugeController::GaugeController(const Glib::WeakPtr<Damageable>& damageable) :
    damageable_{ damageable }
{}

void GaugeController::Start()
{
    gauge_ = GameObject()->GetComponent<Image>();
}

void GaugeController::Update()
{
    if (damageable_.expired()) return;

    const auto& transform = GameObject()->Transform();
    Vector3 scale = transform->LocalScale();
    float hpRate = damageable_->HealthRate();
    float speed = speed_ * GameTimer::UnscaledDeltaTime();
    scale.x = Mathf::Lerp(scale.x, hpRate, speed); // スケールを増減
    scale.x = Mathf::Clamp(scale.x, 0.0f, 1.0f); // ゲージがはみ出さないように制限
    transform->LocalScale(scale);
}

float GaugeController::Speed() const
{
    return speed_;
}

void GaugeController::Speed(float speed)
{
    speed_ = speed;
}

void GaugeController::OnGUI()
{
    GLGUI::DragFloat("Speed", &speed_, 0.1f, 0.01f);
}
