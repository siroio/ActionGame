#include "ClearSceneNavigator.h"
#include <GameObject.h>
#include <GameTimer.h>

#include "../Scene/SceneChanger.h"
#include "../../Constant/SceneName.h"

using namespace Glib;

void ClearSceneNavigator::Start()
{
    auto sceneChanger = GameObject()->GetComponent<SceneChanger>();
    sceneChanger->Change(SceneName::RESULT);
    GameTimer::TimeScale(0.2f);
}
