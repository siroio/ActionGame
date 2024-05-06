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
    Color GAUGE_COLOR{ 0.0f, 1.0f, 0.1f };
    Color GAUGE_BG_COLOR{ 0.2f, 0.2f, 0.2f };
}

void HPGauge::Spawn(const GameObjectPtr& canvas)
{
    auto hpBG = GameObjectManager::Instantiate("HPGaugeBG");
    auto hpGauge = GameObjectManager::Instantiate("HPGauge");
    auto hpFrame = GameObjectManager::Instantiate("HPGaugeFrame");

    hpBG->Transform()->Parent(canvas->Transform());
    hpBG->Transform()->LocalPosition(Vector3{ 120.0f, 70.0f, 0.0f });
    auto hpImageBG = hpBG->AddComponent<Image>();
    hpImageBG->TextureID(TextureID::HP_BG);
    hpImageBG->Center(Vector2::Zero());
    hpImageBG->Color(GAUGE_BG_COLOR);

    auto player = GameObjectManager::Find(ObjectName::Player);
    auto damageable = player->GetComponent<Damageable>();

    hpGauge->Transform()->Parent(hpBG->Transform());
    auto hpImageGauge = hpGauge->AddComponent<Image>();
    auto controller = hpGauge->AddComponent<GaugeController>(damageable);
    controller->Speed(2.0f);
    hpImageGauge->TextureID(TextureID::HP_Gauge);
    hpImageGauge->Center(Vector2::Zero());
    hpImageGauge->Color(GAUGE_COLOR);

    hpFrame->Transform()->Parent(hpBG->Transform());
    auto hpImageFrame = hpFrame->AddComponent<Image>();
    hpImageFrame->TextureID(TextureID::HP_Frame);
    hpImageFrame->Center(Vector2::Zero());
    hpImageFrame->Color(Color::Black());
}
