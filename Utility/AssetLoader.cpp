#include "AssetLoader.h"
#include <GearsUtility/CSVLoader.h>
#include <GearsAudio/AudioManager.h>
#include <GearsEffect/EffectManager.h>
#include <GearsGraphics/AnimationManager.h>
#include <GearsGraphics/MeshManager.h>
#include <GearsGraphics/SkyboxManager.h>
#include <GearsGraphics/TextureManager.h>
#include <unordered_map>
#include <functional>
#include <filesystem>

using namespace Glib;
namespace fs = std::filesystem;

namespace
{
    using LoadFunction = std::function<bool(unsigned int, std::string_view)>;
    std::unordered_map<AssetType, LoadFunction> s_loadFunctions
    {
        { AssetType::Animation, AnimationManager::Load },
        { AssetType::Audio, AudioManager::LoadVoice },
        { AssetType::Effect, EffectManager::Load },
        { AssetType::Mesh, MeshManager::Load },
        { AssetType::Texture, TextureManager::Load },
    };
}

void AssetLoader::Load(std::string_view path, const AssetType& type)
{
    auto csv = Glib::CSVLoader{ path }.Load();
    if (csv.empty()) return;

    for (const auto& row : csv)
    {
        if (row.size() < 2) continue;

        const unsigned id = std::stoi(row[0]); // アセットID

        // アセットまでの絶対パス
        fs::path path{ row[1] };
        const auto& absolutePath = path.is_absolute() ? path : fs::absolute(path);
        if ((type == AssetType::Skybox) && (row.size() > 7))
        {
            std::vector<std::string> params{ row.begin() + 1, row.begin() + 7 };
            for (auto& param : params)
            {
                fs::path path{ param };
                param = (path.is_absolute() ? path : fs::absolute(path)).string();
            }
            LoadSkyBox(id, params);
        }
        else
        {
            s_loadFunctions[type](id, absolutePath.string());
        }
    }
}

void AssetLoader::LoadSkyBox(unsigned int id, const std::vector<std::string>& path)
{
    SkyboxManager::Load(id, path.at(0), path.at(1), path.at(2), path.at(3), path.at(4), path.at(5));
}
