#pragma once
#include <Component.h>

namespace Glib
{
    class Image;
}
enum class Ease;
class Damageable;

/**
 * @brief HPゲージなどの制御用コンポーネント
 */
class GaugeController : public Component
{
public:
    GaugeController(const Glib::WeakPtr<Damageable>& damageable);
    void Start();
    void Update();

    /**
     * @brief ゲージの増減速度を取得
     */
    float Speed() const;

    /**
     * @brief ゲージの増減速度を指定
     * @param speed
     */
    void Speed(float speed);

private:
    void OnGUI() override;

private:
    Glib::WeakPtr<Glib::Image> gauge_{};
    Glib::WeakPtr<Damageable> damageable_{};
    float speed_{ 1.0f };
};
