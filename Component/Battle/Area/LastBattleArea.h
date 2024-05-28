#pragma once
#include <Component.h>

namespace Glib
{
    class EventMsg;
}

class BattleArea;

class LastBattleArea : public Component
{
public:
    void Start();
    void ReceiveMsg(const Glib::EventMsg& msg);

private:
    Glib::WeakPtr<BattleArea> battleArea_{};
};
