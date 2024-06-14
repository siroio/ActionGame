#include "ScreenFader.h"
#include <GameObject.h>
#include <GameObjectManager.h>
#include <Components/Canvas.h>
#include <Components/Image.h>
#include "../../Component/Fade/UIFader.h"
#include "../../Component/Common/ElapsedTimer.h"
#include "../../Enum/TextureID.h"

using namespace Glib;

WeakPtr<UIFader> ScreenFader::Create(float fadeTime, bool onStartFade, TimerScale mode)
{
    auto gameObject = GameObjectManager::Instantiate("ScreenFader");
    auto canvas = gameObject->AddComponent<Canvas>();
    canvas->Order(100);

    auto image = gameObject->AddComponent<Image>();
    image->TextureID(TextureID::Fade);
    image->Center(Vector2::Zero());

    auto fader = gameObject->AddComponent<UIFader>();
    fader->SetEase(Ease::OutQuart);
    fader->SetEndAlpha(0.0f);
    if (onStartFade) fader->StartFade(fadeTime);

    auto timer = gameObject->AddComponent<ElapsedTimer>(mode);

    return fader;
}
