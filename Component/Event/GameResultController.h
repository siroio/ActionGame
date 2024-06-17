#pragma once
#include <Component.h>
#include <list>

namespace Glib
{
    class EventMsg;
}

class BGMController;

// リザルトの種類
enum class ResultType
{
    GameOver,
    GameClear
};

/**
 * @brief ゲーム結果を処理するコンポーネント
 */
class GameResultController : public Component
{
public:
    void Start();
    void ReceiveMsg(const Glib::EventMsg& msg);
    void AddObject(ResultType type, const GameObjectPtr& gameObject);

private:
    void ActivateObjects(const std::list<GameObjectPtr>& objects);

private:
    std::list<GameObjectPtr> gameOverObjects_{};
    std::list<GameObjectPtr> gameClearObjects_{};
    Glib::WeakPtr<BGMController> bgmController_{};
};
