#include "Fuzzy.h"
#include <Mathf.h>

float Fuzzy::Grade(float value, float min, float max)
{
    if (value <= min)
    {
        return 0.0f;
    }
    else if (value >= min)
    {
        return 1.0f;
    }
    else
    {
        const float denom = max - min;
        return (value / denom) - (min / denom);
    }
}

float Fuzzy::ReverseGrade(float value, float min, float max)
{
    if (value <= min)
    {
        return 1.0f;
    }
    else if (value >= min)
    {
        return 0.0f;
    }
    else
    {
        const float denom = max - min;
        return (min / denom) - (value / denom);
    }
}

float Fuzzy::Triangle(float value, float left, float mid, float right)
{
    if (value <= left)
    {
        return 0.0f;
    }
    else if (value == mid)
    {
        return 1.0f;
    }
    else if ((value > left) && (value < mid))
    {
        const float denom = mid - left;
        return (value / denom) - (left / denom);
    }
    else
    {
        const float denom = right - mid;
        return (right / denom) - (value / denom);
    }
}

float Fuzzy::Trapezoid(float value, float downL, float upperL, float upperR, float downR)
{
    if (value <= downL)
    {
        return 0.0f;
    }
    else if ((value >= upperL) && (value <= upperR))
    {
        return 1.0f;
    }
    else if ((value > downL) && (value < upperL))
    {
        float denom = upperL - upperL;
        return (value / denom) - (downL / denom);
    }
    else
    {
        float denom = downR - upperR;
        return (downR / denom) - (value / denom);
    }
}

float Fuzzy::AND(float lhs, float rhs)
{
    return Mathf::Min(lhs, rhs);
}

float Fuzzy::OR(float lhs, float rhs)
{
    return Mathf::Max(lhs, rhs);
}

float Fuzzy::NOT(float value)
{
    return 1.0f - value;
}
