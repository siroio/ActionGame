#include "GameClear.h"
#include <GameObjectManager.h>
#include <GameObject.h>
#include <Color.h>

#include "../UI/ScreenFader/ScreenFader.h"
#include "../../Component/Scene/SceneChanger.h"
#include "../../Component/Fade/UIFader.h"
#include "../../Component/Event/ClearSceneNavigator.h"
#include "../../Enum/TimeScale.h"

using namespace Glib;

namespace
{
    const Color FADE_COLOR{ 1.0f, 1.0f, 1.0f, 0.0f };
}

GameObjectPtr GameClear::Create()
{
    auto gameClearObj = GameObjectManager::Instantiate("GameClear");
    auto fader = ScreenFader::Create(0.0f, false, 0.8f, FADE_COLOR, TimerScale::UnScaled);
    fader->SetEndAlpha(1.0f);
    fader->StartFade(5.0f);
    fader->GameObject()->Transform()->Parent(gameClearObj->Transform());
    gameClearObj->AddComponent<SceneChanger>(fader);
    gameClearObj->AddComponent<ClearSceneNavigator>();
    return gameClearObj;
}
