#pragma once
#include <Component.h>
#include <functional>

namespace Glib
{
    class EffectSystem;
    class EventMsg;
}

struct Vector3;

class EffectSpawner : public Component
{
public:
    using SpawnFunction = std::function<void(const Vector3&)>;

public:
    EffectSpawner(const SpawnFunction& function, unsigned int id);

    void Spawn(const Vector3& position);
    void ReceiveMsg(const Glib::EventMsg& msg);

private:
    SpawnFunction function_{};
    int messageID_{ -1 };
};
