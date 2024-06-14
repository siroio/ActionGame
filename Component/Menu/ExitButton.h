#pragma once
#include "MenuItem.h"

/**
 * @brief 終了ボタン
 */
class ExitButton : public MenuItem
{
public:
    void Comfirm() override;
};
