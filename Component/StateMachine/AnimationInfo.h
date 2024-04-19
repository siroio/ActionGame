#pragma once

struct AnimationInfo
{
    AnimationInfo() = default;
    AnimationInfo(int animationID, float blendTime = 0.1f, float startFrameOffset = 0.0f, bool loop = false) :
        AnimationID{ animationID }, BlendTime{ blendTime },
        StartFrameOffset{ startFrameOffset }, Loop{ loop }
    {}

    int AnimationID{ -1 };
    float BlendTime{ 0.0f };
    float StartFrameOffset{ 0.0f };
    bool Loop{ false };
};
