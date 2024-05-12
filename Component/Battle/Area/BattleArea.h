#pragma once
#include <Component.h>
#include <list>

namespace Glib
{
    class Collider;
    class EventMsg;
}

class Wave;
class BGMController;

class BattleArea : public Component
{
private:
    using WavePtr = Glib::WeakPtr<Wave>;

public:
    void Start();

    /**
     * @brief ウェーブを追加
     */
    void AddtWave(const WavePtr& wave);

    /**
     * @brief ウェーブを開始
     */
    void SetNextWave();

    /**
     * @brief 次ウェーブを確認
     */
    bool HasNextWave() const;

    void OnTriggerEnter(const GameObjectPtr& other);

    void ReceiveMsg(const Glib::EventMsg& msg);

private:
    void StartBattle();
    void StartWave();
    void EndBattle();

private:
    Glib::WeakPtr<Glib::Collider> collider_{};
    Glib::WeakPtr<BGMController> bgmController{};
    WavePtr currentWave_{};
    std::list<WavePtr> waves_{};
};
