#include "App.h"
#include <SceneManager.h>
#include <AudioManager.h>
#include "../Enum/AudioGroupID.h"
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

    constexpr float BGM_VOLIME{ 0.1f };
    constexpr float SE_VOLUME{ 0.1f };
}

void App::Start()
{
    LoadAssets();
    InitializeSound();
    ResiterScenes();
    SceneManager::LoadScene("PlayScene");
}

void App::End()
{}

void App::LoadAssets()
{
    AssetLoader::Load(ANIMATION, AssetType::Animation);
    AssetLoader::Load(AUDIO, AssetType::Audio);
    AssetLoader::Load(EFFECT, AssetType::Effect);
    AssetLoader::Load(MODEL, AssetType::Mesh);
    AssetLoader::Load(SKYBOX, AssetType::Skybox);
}

void App::InitializeSound()
{
    AudioManager::AddSoundGroup(AudioGroupID::BGM);
    AudioManager::AddSoundGroup(AudioGroupID::SE);
    AudioManager::SetSoundGroupVolume(AudioGroupID::BGM, BGM_VOLIME);
    AudioManager::SetSoundGroupVolume(AudioGroupID::SE, SE_VOLUME);
}

void App::ResiterScenes()
{
    SceneManager::Register<TitleScene>();
    SceneManager::Register<PlayScene>();
    SceneManager::Register<ResultScene>();
}
