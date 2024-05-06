#include "ValidityTimer.h"

ValidityTimer::ValidityTimer(float receptionTime, float startTime) :
    receptionTime_{ receptionTime }, startTime_{ startTime }
{}

bool ValidityTimer::Reception(float elapsedTime) const
{
    if (elapsedTime < startTime_) return false;
    return elapsedTime <= (startTime_ + receptionTime_);
}

float ValidityTimer::ReceptionTime() const
{
    return receptionTime_;
}

void ValidityTimer::ReceptionTime(float time)
{
    receptionTime_ = time;
}

float ValidityTimer::StartTime() const
{
    return startTime_;
}

void ValidityTimer::StartTime(float time)
{
    startTime_ = time;
}
