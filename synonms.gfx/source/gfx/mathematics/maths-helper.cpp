#include "maths-helper.h"

using namespace synonms::gfx::mathematics;

float MathsHelper::Gamma(int n) 
{
    return (n * epsilon) / (1 - n * epsilon);
}

bool MathsHelper::IsEqual(float a, float b)
{
    const float d = a - b;
    if (d < epsilon && d > -epsilon)
        return true;
    else
        return false;
}

float MathsHelper::Minimum(float a, float b)
{
    if (a < b)
        return a;
    else
        return b;
}

float MathsHelper::Maximum(float a, float b)
{
    if (a > b)
        return a;
    else
        return b;
}

float MathsHelper::SquareRoot(float value)
{
    if(value < 0) throw std::exception("Value < 0");
    return (float)pow(value, 0.5f);
}

float MathsHelper::DegreesToRadians(float angleInDegrees)
{
    return angleInDegrees * pi / 180.0f;
}

float MathsHelper::RadiansToDegrees(float angleInRadians)
{
    return angleInRadians * 180.0f / pi;
}

float MathsHelper::Sine(float radians)
{
    return (float) ::sin(radians);
}

float MathsHelper::Cosine(float radians)
{
    return (float) ::cos(radians);
}

float MathsHelper::Tangent(float radians)
{
    return (float) ::tan(radians);
}

float MathsHelper::ArcSine(float value)
{
    return (float) ::asin(value);
}

float MathsHelper::ArcCosine(float value)
{
    return (float) ::acos(value);
}

float MathsHelper::ArcTangent(float y, float x)
{
    return (float) ::atan2(y, x);
}

float MathsHelper::Floor(float value)
{
    return (float) ::floor(value);
}

float MathsHelper::Ceiling(float value)
{
    return (float) ::ceil(value);
}

unsigned int MathsHelper::Sign(const float& v)
{
    return (((unsigned int&)v) & 0x80000000);
}

float MathsHelper::Absolute(float v)
{
    *(int*)&v &= 0x7fffffff;
    return v;
}

float MathsHelper::Interpolate(float value0, float value1, float t)
{
    return value0 + (value1 - value0) * t;
}

float MathsHelper::Snap(float p, float grid)
{
    return grid ? float(floor((p + grid * 0.5f) / grid) * grid) : p;
}

float MathsHelper::Power(float base, float exponent)
{
    return ::pow(base, exponent);
}
