#include "GameOver.h"
#include <Components/Canvas.h>
#include <Components/Image.h>
#include <Components/AudioSource.h>
#include <GameObjectManager.h>
#include <GameObject.h>

#include "../../Character/UI/ScreenFader/ScreenFader.h"
#include "../../Character/UI/GameOverMenu/GameOverMenu.h"
#include "../../Component/Common/ElapsedTimer.h"
#include "../../Component/Fade/UIFader.h"
#include "../../Component/Audio/AudioEventPlayer.h"
#include "../../Component/Scene/SceneChanger.h"
#include "../../Enum/TextureID.h"
#include "../../Enum/AudioGroupID.h"
#include "../../Enum/AudioID.h"
#include "../../Enum/MessageID.h"


using namespace Glib;

namespace
{
    constexpr float FADE_DURATION{ 2.5f };
    constexpr float FADE_ALPHA{ 0.8f };
    const Color FADE_COLOR{ 1.0f, 1.0f, 1.0f, 0.0f };
    const Color BG_COLOR{ 0.0f, 0.0f, 0.0f, 0.0f };
    const Vector3 TEXT_POSITION{ 960.0f, 440.0f, 0.0f };
}

GameObjectPtr GameOver::Create()
{
    // ゲームオーバー用のオブジェクト作成
    auto gameOverObj = GameObjectManager::Instantiate("GameOver");

    // キャンバスの作成
    auto gameOverCanvas = GameObjectManager::Instantiate("GameOverCanvas");
    gameOverCanvas->AddComponent<Canvas>();
    gameOverCanvas->Transform()->Parent(gameOverObj->Transform());

    // ゲームオーバー背景
    auto gameOverBG = GameObjectManager::Instantiate("GameOverBG");
    auto bgImg = gameOverBG->AddComponent<Image>();
    bgImg->TextureID(TextureID::Fade);
    bgImg->Color(BG_COLOR);
    bgImg->Center(Vector2::Zero());
    auto bgFader = gameOverBG->AddComponent<UIFader>();
    gameOverBG->AddComponent<ElapsedTimer>();
    bgFader->SetEase(Ease::OutExpo);
    bgFader->SetEndAlpha(FADE_ALPHA);
    bgFader->StartFade(FADE_DURATION);
    gameOverBG->Transform()->Parent(gameOverCanvas->Transform());

    // ゲームオーバーテキスト
    auto gameOverText = GameObjectManager::Instantiate("GameOverText");
    auto textImg = gameOverText->AddComponent<Image>();
    textImg->TextureID(TextureID::GameOver);
    gameOverText->Transform()->Position(TEXT_POSITION);
    gameOverText->Transform()->Parent(gameOverCanvas->Transform());

    // シーン変更オブジェクト
    auto fader = ScreenFader::Create(FADE_DURATION, false, 1.0f, FADE_COLOR, TimerScale::Scaled);
    auto sceneChangerObj = GameObjectManager::Instantiate("SceneChanger");
    auto sceneChanger = sceneChangerObj->AddComponent<SceneChanger>(fader);

    // ゲームーオーバーメニュー
    auto menu = GameOverMenu::Create(gameOverCanvas, sceneChanger);
    menu->AddComponent<AudioSource>()->SetGroup(AudioGroupID::SE);
    menu->AddComponent<AudioEventPlayer>(AudioID::ButtonPush, MessageID::Comfirm);
    menu->AddComponent<AudioEventPlayer>(AudioID::CursorMove, MessageID::CursorMove);

    return gameOverObj;
}
