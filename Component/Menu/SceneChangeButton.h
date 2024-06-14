#pragma once
#include "MenuItem.h"
#include <string>

class SceneChanger;

/**
 * @brief シーン変更ボタン
 */
class SceneChangeButton : public MenuItem
{
public:
    SceneChangeButton(std::string_view sceneName, const Glib::WeakPtr<SceneChanger>& sceneChanger);
    SceneChangeButton(std::string_view sceneName);
    void Comfirm() override;

private:
    std::string sceneName_;
    Glib::WeakPtr<SceneChanger> sceneChanger_{};
};
