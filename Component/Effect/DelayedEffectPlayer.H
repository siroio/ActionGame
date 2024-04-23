#pragma once
#include <Component.h>

namespace Glib
{
    class EffectSystem;
}

class DelayedEffectPlayer
{
public:
    enum class ScaleTime
    {
        Scaled,
        UnScaled,
    };

public:
    void Start();
    void Update();

private:
    Glib::WeakPtr<Glib::EffectSystem> effectSystem_{};
    float elapsedTime_{ 0.0f };
};
