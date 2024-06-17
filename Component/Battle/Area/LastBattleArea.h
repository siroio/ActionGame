#pragma once
#include <Component.h>

namespace Glib
{
    class EventMsg;
}

class BattleArea;
class GameResultController;

/**
 * @brief 最後のエリア用コンポーネント
 */
class LastBattleArea : public Component
{
public:
    void Start();
    void ReceiveMsg(const Glib::EventMsg& msg);

private:
    Glib::WeakPtr<BattleArea> battleArea_{};
    Glib::WeakPtr<GameResultController> resultEventer_{};
};
