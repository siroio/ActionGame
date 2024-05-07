#include "HPGauge.h"
#include <Components/Image.h>
#include <GameObject.h>
#include <GameObjectManager.h>
#include <Vector2.h>
#include <Vector3.h>
#include <Color.h>
#include "../../../Component/Common/GaugeController.h"
#include "../../../Component/Common/Damageable.h"
#include "../../../Constant/GameObjectName.h"
#include "../../../Enum/TextureID.h"

using namespace Glib;

namespace
{
    const Vector3 GAUGE_POSITION{ 120.0f, 70.0f, 0.0f };
    const Color GAUGE_COLOR{ 0.0f, 1.0f, 0.0f };
    const Color GAUGE_BG_COLOR{ 0.2f, 0.2f, 0.2f };
    const Color GAUGE_FRAME_COLOR{ 0.1f, 0.1f, 0.1f };
    constexpr float GAUGE_SPEED{ 20.0f };
}

void HPGauge::Spawn(const GameObjectPtr& canvas)
{
    auto hpBG = GameObjectManager::Instantiate("HPGaugeBG");
    auto hpGauge = GameObjectManager::Instantiate("HPGauge");
    auto hpFrame = GameObjectManager::Instantiate("HPGaugeFrame");

    hpBG->Transform()->Parent(canvas->Transform());
    hpBG->Transform()->LocalPosition(GAUGE_POSITION);
    auto hpImageBG = hpBG->AddComponent<Image>();
    hpImageBG->TextureID(TextureID::HP_BG);
    hpImageBG->Center(Vector2::Zero());
    hpImageBG->Color(GAUGE_BG_COLOR);

    auto player = GameObjectManager::Find(ObjectName::Player);
    auto damageable = player->GetComponent<Damageable>();

    hpGauge->Transform()->Parent(hpBG->Transform());
    auto hpImageGauge = hpGauge->AddComponent<Image>();
    auto controller = hpGauge->AddComponent<GaugeController>(damageable);
    controller->Speed(GAUGE_SPEED);
    hpImageGauge->TextureID(TextureID::HP_Gauge);
    hpImageGauge->Center(Vector2::Zero());
    hpImageGauge->Color(GAUGE_COLOR);

    hpFrame->Transform()->Parent(hpBG->Transform());
    auto hpImageFrame = hpFrame->AddComponent<Image>();
    hpImageFrame->TextureID(TextureID::HP_Frame);
    hpImageFrame->Center(Vector2::Zero());
    hpImageFrame->Color(GAUGE_FRAME_COLOR);
}
