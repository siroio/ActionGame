#include "EffectSpawner.h"
#include <GameObject.h>
#include <EventMsg.h>
#include <Vector3.h>

EffectSpawner::EffectSpawner(const SpawnFunction& function, unsigned int id) :
    function_{ function }, messageID_{ id }
{}

void EffectSpawner::Spawn(const Vector3& position)
{
    if (function_ == nullptr) return;
    const auto& transform = GameObject()->Transform();
    Vector3 spawnPoint = position + transform->Rotation() * transform->Position();
    function_(spawnPoint);
}

void EffectSpawner::ReceiveMsg(const Glib::EventMsg& msg)
{
    if (msg.MsgID() != messageID_) return;
    Spawn(msg.Msg<Vector3>());
}
