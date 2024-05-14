#pragma once
#include <Component.h>
#include <GameObjectPtr.h>
#include <Mathf.h>

namespace Glib
{
    class Transform;
}

class CharacterSearcher : public Component
{
public:
    CharacterSearcher(float fov, float distance = Mathf::POSITIVE_INFINITY, float noticeRange = 1.0f, GameObjectPtr target = nullptr);

    /**
     * @brief 視界の距離を取得
     */
    float Distance() const;

    /**
     * @brief 視界の距離を設定
     */
    void Distance(float distance);

    /**
     * @brief 視界を取得
     * @return 度
     */
    float Fov() const;

    /**
     * @brief 視界を設定
     * @param fov 度
     */
    void Fov(float fov);

    /**
     * @brief ターゲットを取得
     */
    GameObjectPtr Target() const;

    /**
     * @brief ターゲットを設定
     */
    void Target(const GameObjectPtr& target);

    /**
     * @brief ターゲットが視界にいるかどうか
     */
    bool TargetInView() const;


private:
    void OnGUI() override;

private:
    GameObjectPtr target_{};
    float distance_{ };
    float fov_{ 0.0f };
    float noticeRange_{ 0.0f };
};
