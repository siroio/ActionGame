#include "UIFader.h"
#include <Components/Image.h>
#include <GameObject.h>
#include <GameTimer.h>
#include <Mathf.h>

#include "../Common/ElapsedTimer.h"
#include "../../Constant/GameObjectName.h"

using namespace Glib;

void UIFader::Start()
{
    image_ = GameObject()->GetComponent<Image>();
    elapsedTimer_ = GameObject()->GetComponent<ElapsedTimer>();
}

void UIFader::Update()
{
    if (InvalidFader() || !isFade_) return;
    UpdateFade();
}

void UIFader::StartFade(float duration)
{
    isFade_ = true;
    duration_ = duration;
    if (!elapsedTimer_.expired())
    {
        elapsedTimer_->Reset();
    }
    if (!image_.expired())
    {
        startAlpha_ = image_->Color().a;
    }
}

bool UIFader::IsEndFade()
{
    return elapsedTimer_->Elapsed() >= duration_;
}

void UIFader::SetEndAlpha(float endAlpha)
{
    endAlpha_ = endAlpha;
}

void UIFader::SetEase(Ease ease)
{
    easeType_ = ease;
}

void UIFader::UpdateFade()
{
    float t = Easing::Evaluate(easeType_, elapsedTimer_->Elapsed(), duration_);
    float alpha = Mathf::Lerp(startAlpha_, endAlpha_, t);
    Color color = image_->Color();
    color.a = alpha;
    image_->Color(color);
    if (t >= 1.0f) isFade_ = false;
}

bool UIFader::InvalidFader()
{
    return elapsedTimer_.expired() || image_.expired();
}
