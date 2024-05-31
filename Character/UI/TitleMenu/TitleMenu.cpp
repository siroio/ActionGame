#include "TitleMenu.h"
#include <Components/Image.h>
#include <GameObjectManager.h>
#include <GameObject.h>
#include <Vector3.h>
#include <Vector2.h>

#include "../../../Component/Menu/MenuController.h"
#include "../../../Component/Menu/MenuButton.h"
#include "../../../Component/Player/PlayerInput.h"
#include "../../../Constant/GameObjectName.h"
#include "../../../Enum/TextureID.h"

using namespace Glib;

namespace
{
    Vector3 CURSOR_OFFSET{ 100.0f, 0.0f, 0.0f };
}

void TitleMenu::Create(const GameObjectPtr& canvas)
{
    auto menu = GameObjectManager::Instantiate("TitleMenu");
    auto play = GameObjectManager::Instantiate("Play");
    auto exit = GameObjectManager::Instantiate("Exit");
    auto cursor = GameObjectManager::Instantiate("Cursor");

    menu->Transform()->Parent(canvas->Transform());
    play->Transform()->Parent(menu->Transform());
    exit->Transform()->Parent(menu->Transform());
    cursor->Transform()->Parent(menu->Transform());

    auto player = GameObjectManager::Find(ObjectName::Player);
    auto input = player->GetComponent<PlayerInput>();

    auto menuController = menu->AddComponent<MenuController>(input);
    auto playItem = SetupMenuMenuButton(play, Vector3{ 300.0f, 300.0f, 0.0f }, Vector3::Zero(), Vector3::One(), TextureID::Play);
    auto exitItem = SetupMenuMenuButton(exit, Vector3{ 300.0f, 300.0f, 0.0f }, Vector3::Zero(), Vector3::One(), TextureID::Exit);
    menuController->AddFrontItem(playItem);
    menuController->AddFrontItem(exitItem);

    auto cursorImage = cursor->AddComponent<Image>();
    cursorImage->TextureID(TextureID::Cursor);
    menuController->SetCursor(cursor);
    menuController->SetCursorOffset(CURSOR_OFFSET);
}

Glib::WeakPtr<MenuItem> TitleMenu::SetupMenuMenuButton(const GameObjectPtr& item, const Vector3& position, const Vector3& euler, const Vector3& scale, unsigned int textureID)
{
    auto menuItem = item->AddComponent<MenuButton>();
    item->Transform()->LocalPosition(position);
    item->Transform()->LocalEulerAngles(euler);
    item->Transform()->LocalScale(scale);

    auto itemImage = item->AddComponent<Image>();
    itemImage->TextureID(textureID);
    itemImage->Center(Vector2{ 0.5f });
    return menuItem;
}
