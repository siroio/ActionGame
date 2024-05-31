#pragma once
#include <Component.h>
#include <list>

namespace Glib
{
    class EventMsg;
}

/**
 * @brief ゲーム結果を処理するコンポーネント
 */
class GameResultEventer : public Component
{
public:
    void Start();
    void ReceiveEvent(const Glib::EventMsg& msg);

private:
    void ActivateObjects(const std::list<GameObjectPtr>& objects);

private:
    std::list<GameObjectPtr> gameOverObjects_{};
    std::list<GameObjectPtr> gameClearObjects_{};
};
