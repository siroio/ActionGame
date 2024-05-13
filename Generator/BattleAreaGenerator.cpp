#include "BattleAreaGenerator.h"
#include <GameObject.h>
#include <GameObjectManager.h>
#include <Components/Rigidbody.h>
#include <Components/SphereCollider.h>
#include <filesystem>
#include <fstream>
#include <functional>
#include <Json.h>
#include <vector>
#include <unordered_map>
#include <Vector3.h>
#include <Debugger.h>

#include "../Component/Battle/Area/BattleArea.h"
#include "../Component/Battle/Wave/Wave.h"
#include "../Component/Common/ElapsedTimer.h"
#include "../Character/Enemy/Golem/Golem.h"
#include "../Character/Enemy/Mage/Mage.h"
#include "../Character/Enemy/Skeleton/Skeleton.h"
#include "../Enum/CollisionLayer.h"

namespace fs = std::filesystem;
using namespace Glib;
using namespace nlohmann;

namespace
{
    constexpr char AREA_NAME[]{ "AreaName" };
    constexpr char AREA_RANGE[]{ "Range" };
    constexpr char AREA_WAVES[]{ "Waves" };

    constexpr char WAVE_NAME[]{ "WaveName" };
    constexpr char WAVE_ENEMIES[]{ "Enemies" };

    constexpr char ENEMY_TYPE[]{ "EnemyType" };

    constexpr char POSITION[]{ "Position" };
    constexpr char EULER[]{ "Euler" };
    constexpr char SCALE[]{ "Scale" };
}

namespace
{
    struct EnemyData
    {
        std::string type;
        Vector3 position;
        Vector3 euler;
        Vector3 scale;
    };

    struct WaveData
    {
        std::string name;
        std::vector<EnemyData> enemies;
    };

    struct BattleAreaData
    {
        std::string name;
        float range{ 0.0f };
        Vector3 position;
        std::vector<WaveData> waves;
    };

    std::unordered_map<std::string, std::function<GameObjectPtr(const Vector3&, const Vector3&, const Vector3&)>> createFunctions{
        { "Skeleton", Skeleton::Spawn },
        { "Mage", Mage::Spawn },
        { "Golem", Golem::Spawn },
    };
}

void BattleAreaGenerator::Generate(std::string_view filePath)
{
    fs::directory_iterator files{ filePath };
    std::vector<json> areaData{};
    for (const auto& entry : files)
    {
        const auto& path = entry.path();
        // json以外はスキップ
        if (path.extension() != ".json") continue;
        std::ifstream file{ path };

        // 開けているか確認
        if (!file.is_open()) continue;

        // 読み込み
        json jsonFile{};
        file >> jsonFile;
        areaData.push_back(jsonFile);
    }

    std::vector<BattleAreaData> areas{};
    try
    {
        // エリアの読み込み
        for (const auto& data : areaData)
        {
            BattleAreaData area;
            area.name = data[AREA_NAME].get<std::string>();
            area.range = data[AREA_RANGE].get<float>();
            const auto& areaPos = data[POSITION];
            area.position = Vector3{ areaPos["X"], areaPos["Y"], areaPos["Z"] };

            const auto& waves = data[AREA_WAVES];
            if (waves == nullptr) continue;

            // ウェーブの読み込み
            for (const auto& waveData : waves)
            {
                WaveData wave;
                wave.name = waveData[WAVE_NAME].get<std::string>();
                const auto& enemies = waveData[WAVE_ENEMIES];
                if (enemies == nullptr) continue;

                // 敵の読み込み
                for (const auto& enemyData : enemies)
                {
                    EnemyData enemy;
                    enemy.type = enemyData[ENEMY_TYPE].get<std::string>();
                    const auto& position = enemyData[POSITION];
                    const auto& euler = enemyData[EULER];
                    const auto& scale = enemyData[SCALE];

                    enemy.position = Vector3{ position["X"], position["Y"], position["Z"] };
                    enemy.euler = Vector3{ euler["X"], euler["Y"], euler["Z"] };
                    enemy.scale = Vector3{ scale["X"], scale["Y"], scale["Z"] };
                    wave.enemies.push_back(std::move(enemy));
                }
                area.waves.push_back(std::move(wave));
            }
            areas.push_back(std::move(area));
        }
    }
    catch (const std::exception& ex)
    {
        Debug::Error("BattleAreaの読み込みに失敗しました。");
        Debug::Error(ex.what());
    }

    for (const auto& area : areas)
    {
        GameObjectPtr areaObject = GameObjectManager::Instantiate(area.name);
        areaObject->Transform()->Position(area.position);
        areaObject->Layer(CollisionLayer::BattleArea);
        areaObject->AddComponent<ElapsedTimer>();
        auto areaRigidbody = areaObject->AddComponent<Rigidbody>();
        auto areaCollider = areaObject->AddComponent<SphereCollider>();
        auto battleArea = areaObject->AddComponent<BattleArea>();

        areaRigidbody->IsKinematic(true);
        areaCollider->IsTrigger(true);
        areaCollider->IsVisible(true);
        areaCollider->Radius(area.range);

        for (const auto& wave : area.waves)
        {
            auto waveObject = GameObjectManager::Instantiate(wave.name);
            waveObject->Transform()->Parent(areaObject->Transform());
            auto waveComp = waveObject->AddComponent<Wave>(1.0f);
            battleArea->AddtWave(waveComp);

            for (const auto& enemy : wave.enemies)
            {
                const auto& createFunction = createFunctions.find(enemy.type);
                if (createFunction == createFunctions.end()) return;
                GameObjectPtr enemyObject = createFunction->second(enemy.position, enemy.euler, enemy.scale);
                enemyObject->Transform()->Parent(waveObject->Transform());
            }
            waveObject->Active(false);
        }
    }
}
