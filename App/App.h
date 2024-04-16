#pragma once
#include <GearsCore/Glib.h>
#include <GearsCore/Game.h>

class App : public Glib::Game
{
public:
    App() = default;
    void Start() override;
    void End() override;

private:
    void LoadAssets();
    void InitializeSound();
    void ResiterScenes();
};
