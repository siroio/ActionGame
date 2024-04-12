#include "ReceptionTimer.h"

ReceptionTimer::ReceptionTimer(float receptionTime, float startTime) :
    receptionTime_{ receptionTime }, startTime_{ startTime }
{}

bool ReceptionTimer::Reception(float elapsedTime) const
{
    if (elapsedTime < startTime_) return false;
    return elapsedTime <= (startTime_ + receptionTime_);
}

float ReceptionTimer::ReceptionTime() const
{
    return receptionTime_;
}

float ReceptionTimer::StartTime() const
{
    return startTime_;
}
