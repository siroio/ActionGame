#pragma once
#include <Component.h>
#include <list>

namespace Glib
{
    class SphereCollider;
    class EventMsg;
}

class Wave;

class BattleArea : public Component
{
private:
    using WavePtr = Glib::WeakPtr<Wave>;

public:
    void Start();
    void Update();

    /**
     * @brief ウェーブを追加
     */
    void AddtWave(const WavePtr& wave);

    /**
     * @brief ウェーブを開始
     */
    void StartNextWave();

    /**
     * @brief 次ウェーブを確認
     */
    bool HasNextWave() const;

    void OnTriggerEnter(const GameObjectPtr& other);

    void ReceiveMsg(const Glib::EventMsg& msg);

private:
    void StartBattle();
    void EndBattle();

private:
    float range_{ 0.0f };
    Glib::WeakPtr<Glib::SphereCollider> collider_{};
    WavePtr currentWave_{};
    std::list<WavePtr> waves_{};
};
