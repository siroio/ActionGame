#include "CameraObstacleDetection.h"
#include <GameObject.h>
#include <Physics.h>
#include <RaycastHit.h>
#include <algorithm>

#include "CameraController.h"
#include "../../Constant/ObjectTag.h"
#include <GLGUI.h>

using namespace Glib;

void CameraObstacleDetection::Start()
{
    controller_ = GameObject()->GetComponent<CameraController>();
}

void CameraObstacleDetection::FixedUpdate()
{
    auto parameter = controller_->GetParameter();
    const auto& target = parameter.Target;
    const auto& transform = GameObject()->Transform();
    if (target.expired()) return;

    Vector3 direction = transform->Position() - target->Position();

    std::vector<RaycastHit> hits{};
    bool isHit = Physics::RaycastAll(target->Position(), direction, hits, parameter.Distance);
    if (!isHit) return;

    // 距離を昇順でソート
    std::sort(hits.begin(), hits.end(), [](const RaycastHit& lhs, const RaycastHit& rhs)
    {
        return lhs.distance < rhs.distance;
    });
    for (const auto& hit : hits)
    {
        const auto& go = hit.gameObject;
        if (go.expired()) continue;
        if (go->Tag() != GameTag::OBSTACLE) continue;
        if (hit.distance > parameter.Distance) continue;
        parameter.Position = (parameter.Position * -offset_);
        break;
    }

    controller_->SetParameter(parameter);
}

void CameraObstacleDetection::OnGUI()
{
    GLGUI::DragFloat("Offset", &offset_, 0.1f, 0.0f);
}
