#pragma once
#include <GearsCore/Glib.h>
#include <GearsCore/Game.h>

class App : public Glib::Game
{
public:
    App();
    void Start() override;
    void End() override;

private:
    void ResisterScenes();
    void ResisterInputs();
    void InitializeSound();
    void LoadAssets();
};
