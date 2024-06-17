#pragma once

namespace Glib
{
    template<class T>
    class WeakPtr;
}

struct Color;
class UIFader;
enum class TimerScale;

struct ScreenFader
{
    static Glib::WeakPtr<UIFader> Create(float fadeTime, bool onStartFade, float endAlpha, const Color& color, TimerScale mode);
};
