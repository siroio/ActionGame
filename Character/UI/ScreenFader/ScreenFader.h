#pragma once

namespace Glib
{
    template<class T>
    class WeakPtr;
}

class UIFader;
enum class TimerScale;

struct ScreenFader
{
    static Glib::WeakPtr<UIFader> Create(float fadeTime, bool onStartFade, TimerScale mode);
};
