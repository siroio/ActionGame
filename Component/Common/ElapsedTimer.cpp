#include "ElapsedTimer.h"
#include <GameTimer.h>
#include <GLGUI.h>
#include <string>

namespace
{
    const char* const MEASURE_TYPE[2]{ "Scaled", "Unscaled" };
}

ElapsedTimer::ElapsedTimer(const TimerScale& mode) :
    mode_{ mode }
{}

void ElapsedTimer::Update()
{
    float deltaTime = mode_ == TimerScale::Scaled ?
        Glib::GameTimer::DeltaTime() :
        Glib::GameTimer::UnscaledDeltaTime();

    elapsedTime_ += deltaTime;
}

void ElapsedTimer::Reset()
{
    elapsedTime_ = 0.0f;
}

float ElapsedTimer::Elapsed() const
{
    return elapsedTime_;
}

void ElapsedTimer::OnGUI()
{
    std::string label{ "Measure Type: " };
    Glib::GLGUI::Text(label + MEASURE_TYPE[static_cast<unsigned int>(mode_)]);
    std::string timeLabel{ "Elapsed Time: " };
    Glib::GLGUI::Text(timeLabel + std::to_string(elapsedTime_));
}
