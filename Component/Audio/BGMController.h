#pragma once
#include <Component.h>

namespace Glib
{
    class AudioSource;
}
class AudioFader;

class BGMController : public Component
{
public:
    void Start();
    void Update();
    void Change(unsigned int id);

private:
    Glib::WeakPtr<Glib::AudioSource> audioSource_{};
    Glib::WeakPtr<AudioFader> fader_{};
    int nextBGMID{ -1 };
};
