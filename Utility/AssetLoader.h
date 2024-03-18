#pragma once
#include <string>
#include <vector>

enum class AssetType
{
    Animation,
    Audio,
    Effect,
    Mesh,
    Texture,
    Skybox,
};

class AssetLoader
{
public:
    static void Load(std::string_view path, const AssetType& type);

private:
    static void LoadSkyBox(unsigned int id, const std::vector<std::string>& path);
};
