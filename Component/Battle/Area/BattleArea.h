#pragma once
#include <Component.h>
#include <queue>

namespace Glib
{
    class SphereCollider;
    class EventMsg;
}

class Wave;

class BattleArea : public Component
{
public:
    void Start();

    /**
     * @brief 開始ウェーブを設定
     */
    void SetStartWave(const Glib::WeakPtr<Wave>& wave);

    void OnTriggerEnter(const GameObjectPtr& other);

    void ReceiveEvent(const Glib::EventMsg& msg);

private:
    void StartBattle();
    void EndBattle();

private:
    float range_{ 0.0f };
    Glib::WeakPtr<Glib::SphereCollider> collider_{};
    Glib::WeakPtr<Wave> startWave_{};
};
