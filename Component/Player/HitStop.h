#pragma once
#include <Component.h>

namespace Glib
{
    class EventMsg;
}

class HitStop : public Component
{
public:
    HitStop(unsigned int msgID, float duration, float timeScale);
    void Update();
    void ReceiveMsg(const Glib::EventMsg& msg);

private:
    void OnGUI() override;

private:
    bool hitStop_{ false };
    float duration_{ 0.0f };
    float elapsedTime_{ 0.0f };
    float hitTimeScale_{ 0.0f };
    int msgID_{ -1 };
};
