#include "HitStop.h"
#include <EventMsg.h>
#include <GameTimer.h>
#include <GLGUI.h>

using namespace Glib;

HitStop::HitStop(unsigned int msgID, float duration, float timeScale) :
    msgID_{ static_cast<int>(msgID) }, duration_{ duration }, hitTimeScale_{ timeScale }
{}

void HitStop::Update()
{
    if (!hitStop_) return;

    if (elapsedTime_ >= duration_)
    {
        hitStop_ = false;
        elapsedTime_ = 0.0f;
        GameTimer::TimeScale(1.0f);
        return;
    }

    elapsedTime_ += GameTimer::UnscaledDeltaTime();
}

void HitStop::ReceiveMsg(const EventMsg& msg)
{
    if (msg.MsgID() != msgID_) return;

    hitStop_ = true;
    elapsedTime_ = 0.0f;
    GameTimer::TimeScale(hitTimeScale_);
}

void HitStop::OnGUI()
{
    GLGUI::DragFloat("Duration", &duration_);
    GLGUI::DragFloat("HitTimeScale", &hitTimeScale_);
}
