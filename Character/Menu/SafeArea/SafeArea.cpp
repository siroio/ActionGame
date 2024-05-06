#include "SafeArea.h"
#include <GameObject.h>
#include <GameObjectManager.h>
#include <Components/Canvas.h>
#include <Components/Image.h>

#include "../../Enum/TextureID.h"

using namespace Glib;

void SafeArea::Spawn()
{
    auto canvas = GameObjectManager::Instantiate("SafeAreaCanvas");
    canvas->Active(false);
    canvas->AddComponent<Canvas>();

    auto safeArea = GameObjectManager::Instantiate("SafeArea");
    safeArea->Transform()->Parent(canvas->Transform());
    auto image = safeArea->AddComponent<Image>();
    image->TextureID(TextureID::SafeArea);
    image->Center(Vector2::Zero());
}
