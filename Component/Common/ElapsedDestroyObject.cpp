#include "ElapsedDestroyObject.h"
#include <GameObject.h>
#include "ElapsedTimer.h"

ElapsedDestroyObject::ElapsedDestroyObject(float time) :
    destroyTime_{ time }
{}

void ElapsedDestroyObject::Start()
{
    timer_ = GameObject()->GetComponent<ElapsedTimer>();
}

void ElapsedDestroyObject::Update()
{
    if (timer_.expired()) return;
    if (timer_->Elapsed() >= destroyTime_)
    {
        GameObject()->Destroy();
    }
}
