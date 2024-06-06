#pragma once
#include <Component.h>
#include <string_view>

class UIFader;

class SceneChanger : public Component
{
public:
    SceneChanger(const Glib::WeakPtr<UIFader>& fader);
    void Update();
    void Change(std::string_view scene, float duration);
    void Change(std::string_view scene);

private:
    Glib::WeakPtr<UIFader> fader_{};
    std::string nextScene_{};
    bool isChange_{ false };
};
