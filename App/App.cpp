#include "App.h"
#include <Glib.h>
#include <SceneManager.h>
#include <AudioManager.h>
#include <InputSystem.h>
#include <Physics.h>
#include <Window.h>
#include <Vector2.h>

#include "../Constant/SceneName.h"
#include "../Enum/AudioGroupID.h"
#include "../Enum/CollisionLayer.h"
#include "../Scene/TitleScene.h"
#include "../Scene/PlayScene.h"
#include "../Scene/ResultScene.h"
#include "../Utility/AssetLoader.h"

using namespace Glib;

namespace
{
    constexpr char ANIMATION[]{ "Assets/List/Animation.csv" };
    constexpr char AUDIO[]{ "Assets/List/Audio.csv" };
    constexpr char EFFECT[]{ "Assets/List/Effect.csv" };
    constexpr char MODEL[]{ "Assets/List/Model.csv" };
    constexpr char SKYBOX[]{ "Assets/List/Skybox.csv" };
    constexpr char TEXTURE[]{ "Assets/List/Texture.csv" };

    constexpr float BGM_VOLIME{ 0.1f };
    constexpr float SE_VOLUME{ 0.1f };
}

App::App()
{
    Window::BorderlessWindow(true);
    Window::WindowSize(Vector2{ 1920.0f, 1080.0f });
    Window::WindowDebugSize(Vector2{ 1408.0f, 792.0f });
}

void App::Start()
{
    LoadAssets();
    InitializeSound();
    ResisterScenes();
    ResisterInputs();

    // 当たり判定のレイヤー設定
    Physics::SetCollisionFlag(CollisionLayer::Player, CollisionLayer::PlayerAttack, false);

    Physics::SetCollisionFlag(CollisionLayer::PlayerAttack, CollisionLayer::BattleArea, false);
    Physics::SetCollisionFlag(CollisionLayer::PlayerAttack, CollisionLayer::Stage, false);

    Physics::SetCollisionFlag(CollisionLayer::Enemy, CollisionLayer::EnemyAttack, false);
    Physics::SetCollisionFlag(CollisionLayer::Enemy, CollisionLayer::BattleArea, false);

    Physics::SetCollisionFlag(CollisionLayer::EnemyAttack, CollisionLayer::PlayerAttack, false);
    Physics::SetCollisionFlag(CollisionLayer::EnemyAttack, CollisionLayer::BattleArea, false);
    Physics::SetCollisionFlag(CollisionLayer::EnemyAttack, CollisionLayer::Stage, false);

    Physics::SetCollisionFlag(CollisionLayer::BattleArea, CollisionLayer::BattleArea, false);
    Physics::SetCollisionFlag(CollisionLayer::BattleArea, CollisionLayer::Stage, false);

    // タイトルの読み込み
    SceneManager::LoadScene(SceneName::TITLE);
}

void App::End()
{}

void App::ResisterScenes()
{
    SceneManager::Register<TitleScene>();
    SceneManager::Register<PlayScene>();
    SceneManager::Register<ResultScene>();
}

void App::InitializeSound()
{
    AudioManager::AddSoundGroup(AudioGroupID::BGM);
    AudioManager::AddSoundGroup(AudioGroupID::SE);
    AudioManager::SetSoundGroupVolume(AudioGroupID::BGM, BGM_VOLIME);
    AudioManager::SetSoundGroupVolume(AudioGroupID::SE, SE_VOLUME);
}

void App::ResisterInputs()
{
    // メニュー
    InputSystem::AddInput("Pose", GPADKey::START);
    InputSystem::AddInput("Confirm", GPADKey::A);
    InputSystem::AddInput("Deny", GPADKey::B);
    InputSystem::AddInput("Up", GPADKey::UP);
    InputSystem::AddInput("Down", GPADKey::DOWN);

    // プレイ
    InputSystem::AddInput("Attack", GPADKey::B);
    InputSystem::AddInput("Dodge", GPADKey::A);
}

void App::LoadAssets()
{
    AssetLoader::Load(ANIMATION, AssetType::Animation);
    AssetLoader::Load(AUDIO, AssetType::Audio);
    AssetLoader::Load(EFFECT, AssetType::Effect);
    AssetLoader::Load(MODEL, AssetType::Mesh);
    AssetLoader::Load(SKYBOX, AssetType::Skybox);
    AssetLoader::Load(TEXTURE, AssetType::Texture);
}
