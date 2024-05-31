#include "MenuButton.h"
#include <GameObject.h>
#include <Debugger.h>

using namespace Glib;

void MenuButton::Comfirm()
{
    Debug::Log("Comfirm: " + GameObject()->Name());
}

void MenuButton::Deny()
{
    Debug::Log("Deny: " + GameObject()->Name());
}

void MenuButton::Selected()
{
    Debug::Log("Selected: " + GameObject()->Name());
}
