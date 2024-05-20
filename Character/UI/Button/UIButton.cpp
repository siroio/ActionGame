#include "UIButton.h"
#include <Components/Image.h>
#include <GameObjectManager.h>
#include <GameObject.h>

#include "../../Enum/TextureID.h"

using namespace Glib;

namespace
{
    const Vector3 IMAGE_POSITION{ 50.f, 100.0f, 0.0f };
    const Vector3 IMAGE_SCALE{ 0.5f, 0.5f, 1.0f };
}

void UIButton::Spawn(const GameObjectPtr& canvas)
{
    auto buttonUI = GameObjectManager::Instantiate("Button");
    buttonUI->Transform()->Parent(canvas->Transform());
    buttonUI->Transform()->LocalPosition(IMAGE_POSITION);
    buttonUI->Transform()->LocalScale(IMAGE_SCALE);
    auto image = buttonUI->AddComponent<Image>();
    image->TextureID(TextureID::Button);
    image->Center(Vector2::Zero());
}
