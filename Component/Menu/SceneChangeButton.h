#pragma once
#include "MenuItem.h"
#include <string>

class SceneChangeButton : public MenuItem
{
public:
    SceneChangeButton(std::string_view sceneName);
    void Comfirm() override;

private:
    std::string sceneName_;
};
