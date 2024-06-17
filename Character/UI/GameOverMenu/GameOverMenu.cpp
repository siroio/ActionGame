#include "GameOverMenu.h"
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
    const Vector3 PLAY_BUTTON_POS{ 780.0f, 750.0f, 0.0f };
    const Vector3 EXIT_BUTTON_POS{ 800.0f, 900.0f, 0.0f };
    const Vector3 CURSOR_OFFSET{ -35.0f, 0.0f, 0.0f };
    const Vector3 CURSOR_SCALE{ 0.5f, 0.5f, 1.0f };
}

namespace
{
    template<class T, class... Args> requires std::derived_from<T, MenuItem>
    Glib::WeakPtr<MenuItem> SetupButton(const GameObjectPtr& item,
                                        const Vector3& position,
                                        unsigned int textureID, Args&&... args)
    {
        auto menuItem = item->AddComponent<T>(std::forward<Args>(args)...);
        item->Transform()->LocalPosition(position);

        auto itemImage = item->AddComponent<Image>();
        itemImage->TextureID(textureID);
        itemImage->Center(Vector2{ 0.0f, 0.5f });
        return menuItem;
    }
}

GameObjectPtr GameOverMenu::Create(const GameObjectPtr& canvas, const Glib::WeakPtr<SceneChanger>& sceneChanger)
{
    auto menu = GameObjectManager::Instantiate("GameOverMenu");
    auto retry = GameObjectManager::Instantiate("Retry");
    auto exit = GameObjectManager::Instantiate("Title");
    auto cursor = GameObjectManager::Instantiate("Cursor");

    menu->Transform()->Parent(canvas->Transform());
    retry->Transform()->Parent(menu->Transform());
    exit->Transform()->Parent(menu->Transform());
    cursor->Transform()->Parent(menu->Transform());

    auto input = GameObjectManager::Find(ObjectName::Player)->GetComponent<PlayerInput>();

    auto menuController = menu->AddComponent<MenuController>(input);
    auto retryItem = SetupButton<SceneChangeButton>(retry, PLAY_BUTTON_POS, TextureID::Retry, SceneName::PLAY, sceneChanger);
    auto titleItem = SetupButton<SceneChangeButton>(exit, EXIT_BUTTON_POS, TextureID::Title, SceneName::TITLE, sceneChanger);
    menuController->AddBackItem(retryItem);
    menuController->AddBackItem(titleItem);

    auto cursorImage = cursor->AddComponent<Image>();
    cursorImage->TextureID(TextureID::Cursor);
    menuController->SetCursor(cursor);
    menuController->SetCursorOffset(CURSOR_OFFSET);
    cursor->Transform()->LocalScale(CURSOR_SCALE);

    return menu;
}
