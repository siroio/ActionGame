#pragma once

struct AnimationInfo
{
    AnimationInfo() = default;
    AnimationInfo(int animationID, float frameOffset = 0.0f, float blendTime = 0.1f, float speed = 1.0f, bool loop = false) :
        AnimationID{ animationID }, FrameOffset{ frameOffset },
        BlendTime{ blendTime }, Speed{ speed }, Loop{ loop }
    {}

    int AnimationID{ -1 };
    float BlendTime{ 0.0f };
    float FrameOffset{ 0.0f };
    float Speed{ 0.0f };
    bool Loop{ false };
};
