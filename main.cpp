#include <wtypes.h>
#include "App/App.h"

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    return App{}.Run();
}
