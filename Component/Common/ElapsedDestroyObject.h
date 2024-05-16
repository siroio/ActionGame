#pragma once
#include <Component.h>

class ElapsedTimer;

class ElapsedDestroyObject : public Component
{
public:
    ElapsedDestroyObject(float time);
    void Start();
    void Update();

private:
    Glib::WeakPtr<ElapsedTimer> timer_{};
    float destroyTime_{ 0.0f };
};
