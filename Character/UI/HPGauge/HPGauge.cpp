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
    const Color GAUGE_COLOR{ 0.0f, 1.0f, 0.0f, 1.0f };
    const Color GAUGE_DAMAGED_COLOR{ 1.0f, 0.3f, 0.0f, 0.7f };
    const Color GAUGE_BG_COLOR{ 0.2f, 0.2f, 0.2f, 0.6f };
    const Color GAUGE_FRAME_COLOR{ 0.1f, 0.1f, 0.1f, 1.0f };
    constexpr float GAUGE_SPEED{ 20.0f };
    constexpr float GAUGE_DAMAGED_SPEED{ 3.0f };
}

void HPGauge::Spawn(const GameObjectPtr& canvas)
{
    auto hpBG = GameObjectManager::Instantiate("HPGaugeBG");
    auto hpDamagedGauge = GameObjectManager::Instantiate("HPDamagedGauge");
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

    hpDamagedGauge->Transform()->Parent(hpBG->Transform());
    auto hpDamagedImage = hpDamagedGauge->AddComponent<Image>();
    auto hpDamagedController = hpDamagedGauge->AddComponent<GaugeController>(damageable);
    hpDamagedController->Speed(GAUGE_DAMAGED_SPEED);
    hpDamagedImage->TextureID(TextureID::HP_Gauge);
    hpDamagedImage->Center(Vector2::Zero());
    hpDamagedImage->Color(GAUGE_DAMAGED_COLOR);

    hpGauge->Transform()->Parent(hpBG->Transform());
    auto hpGaugeImage = hpGauge->AddComponent<Image>();
    auto hpController = hpGauge->AddComponent<GaugeController>(damageable);
    hpController->Speed(GAUGE_SPEED);
    hpGaugeImage->TextureID(TextureID::HP_Gauge);
    hpGaugeImage->Center(Vector2::Zero());
    hpGaugeImage->Color(GAUGE_COLOR);

    hpFrame->Transform()->Parent(hpBG->Transform());
    auto hpImageFrame = hpFrame->AddComponent<Image>();
    hpImageFrame->TextureID(TextureID::HP_Frame);
    hpImageFrame->Center(Vector2::Zero());
    hpImageFrame->Color(GAUGE_FRAME_COLOR);
}
