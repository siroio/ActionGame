#include "ResultMenu.h"
#include <Components/Image.h>
#include <GameObjectManager.h>
#include <GameObject.h>
#include <Vector3.h>
#include <Vector2.h>
#include <Debugger.h>

#include "../../../Component/Menu/MenuController.h"
#include "../../../Component/Menu/SceneChangeButton.h"
#include "../../../Component/Player/PlayerInput.h"
#include "../../../Constant/GameObjectName.h"
#include "../../../Constant/SceneName.h"
#include "../../../Enum/TextureID.h"

using namespace Glib;

namespace
{
    const Vector3 TITLE_BUTTON_POSITION{ 800.0f, 750.0f, 0.0f };
    const Vector3 RETRY_BUTTON_POS{ 800.0f, 900.0f, 0.0f };
}

GameObjectPtr ResultMenu::Create(const GameObjectPtr& canvas, const Glib::WeakPtr<SceneChanger>& sceneChanger)
{
    auto menu = GameObjectManager::Instantiate("ResultMenu");
    auto clearImg = GameObjectManager::Instantiate("GameClearImg");
    auto titleItem = GameObjectManager::Instantiate("Title");
    auto cursor = GameObjectManager::Instantiate("cursor");

    menu->Transform()->Parent(canvas->Transform());
    clearImg->Transform()->Parent(menu->Transform());
    titleItem->Transform()->Parent(menu->Transform());
    cursor->Transform()->Parent(menu->Transform());

    auto input = GameObjectManager::Find(ObjectName::Player)->GetComponent<PlayerInput>();

    auto menuItem = titleItem->AddComponent<SceneChangeButton>(SceneName::TITLE, sceneChanger);
    titleItem->Transform()->LocalPosition(TITLE_BUTTON_POSITION);
    auto itemImage = titleItem->AddComponent<Image>();
    itemImage->TextureID(TextureID::Title);
    itemImage->Center(Vector2{ 0.0f, 0.5f });

    auto menuController = menu->AddComponent<MenuController>(input);
    menuController->AddBackItem(menuItem);

    return menu;
}
