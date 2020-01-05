#pragma once

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace mathematics
        {
            const float epsilon = 0.00001f;                         ///< floating point epsilon for single precision. todo: verify epsilon value and usage
            const float epsilonSquared = epsilon * epsilon;         ///< epsilon value squared
            const float pi = 3.1415926f;                            ///< pi stored at a reasonable precision for single precision floating point.

            class MathsHelper
            {
            public:
                static float Gamma(int n);

                /// test for floating point equality within [-epsilon,+epsilon]
                static bool IsEqual(float a, float b);

                /// determine the minimum floating point value
                static float Minimum(float a, float b);

                /// determine the maximum floating point value
                static float Maximum(float a, float b);

                /// calculate the square root of a floating point number.
                static float SquareRoot(float value);

                /// convert degrees to radians
                static float DegreesToRadians(float angleInDegrees);

                /// convert degrees to radians
                static float RadiansToDegrees(float angleInRadians);

                /// calculate the sine of a floating point angle in radians.
                static float Sine(float radians);

                /// calculate the cosine of a floating point angle in radians.
                static float Cosine(float radians);

                /// calculate the tangent of a floating point angle in radians.
                static float Tangent(float radians);

                /// calculate the arcsine of a floating point value. result is in radians.
                static float ArcSine(float value);

                /// calculate the arccosine of a floating point value. result is in radians.
                static float ArcCosine(float value);

                /// calculate the arctangent of a floating point value y/x. result is in radians.
                static float ArcTangent(float y, float x);

                /// calculate the floor of a floating point value.
                /// the floor is the nearest integer strictly less than or equal to the floating point number.
                static float Floor(float value);

                /// calculate the ceiling of a floating point value.
                /// the ceil is the nearest integer strictly greater than or equal to the floating point number.
                static float Ceiling(float value);

                /// quickly determine the sign of a floating point number.
                static unsigned int Sign(const float& v);

                /// fast floating point absolute value.
                static float Absolute(float v);

                /// interpolate between interval [a,b] with t in [0,1].
                static float Interpolate(float a, float b, float t);

                /// snap floating point number to grid.
                static float Snap(float p, float grid);

                /// Base raised to the power exponent
                static float Power(float base, float exponent);

                /// Clamp number to a given range
                template <typename T>
                static T Clamp(const T& _value, const T& _min, const T& _max)
                {
                    if (_value < _min) return _min;
                    if (_value > _max) return _max;
                    return _value;
                }
            };
        }
    }
}