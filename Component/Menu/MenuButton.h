#pragma once
#include "MenuItem.h"

class MenuButton : public MenuItem
{
public:
    void Comfirm() override;
    void Deny() override;
    void Selected() override;
};
