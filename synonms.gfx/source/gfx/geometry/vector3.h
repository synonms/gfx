#pragma once

#include <gfx\enumerators\axis3.h>
#include <gfx\mathematics\maths-helper.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace geometry
        {
            template <typename T>
            class Vector3
            {
            public:
                union
                {
                    T x;
                    T red;
                    T pitch;
                };
                union
                {
                    T y;
                    T green;
                    T yaw;
                };
                union
                {
                    T z;
                    T blue;
                    T roll;
                };

            public:
                Vector3(T value1 = static_cast<T>(0), T value2 = static_cast<T>(0), T value3 = static_cast<T>(0))
                    : x(value1), y(value2) , z(value3)
                {
                }

                Vector3(const Vector3<T>& other) 
                    : x(other.x), y(other.y), z(other.z)
                {
                }

                Vector3(Vector3<T>&& other) noexcept
                    : x(std::move(other.x)) , y(std::move(other.y)), z(std::move(other.z))
                {
                }

                void operator=(const Vector3<T>& other)
                {
                    x = other.x;
                    y = other.y;
                    z = other.z;
                }

                void operator=(Vector3<T>&& other) noexcept
                {
                    x = std::move(other.x);
                    y = std::move(other.y);
                    z = std::move(other.z);
                }

            public:
                void operator+=(const Vector3<T>& other)
                {
                    x += other.x;
                    y += other.y;
                    z += other.z;
                }

                void operator-=(const Vector3<T>& other)
                {
                    x -= other.x;
                    y -= other.y;
                    z -= other.z;
                }

                void operator*=(const Vector3<T>& other)
                {
                    x *= other.x;
                    y *= other.y;
                    z *= other.z;
                }

                void operator/=(const Vector3<T>& other)
                {
                    x /= other.x;
                    y /= other.y;
                    z /= other.z;
                }

                T operator[](enumerators::Axis3 axis) const
                {
                    switch (axis)
                    {
                    case enumerators::Axis3::X: return x;
                    case enumerators::Axis3::Y: return y;
                    case enumerators::Axis3::Z: return z;
                    }
                }

            public:
                Vector3<T> Add(const Vector3<T>& other) const { 
                    return *this + other; 
                }

                void Clamp(float min, float max)
                {
                    x = mathematics::MathsHelper::Clamp(x, min, max);
                    y = mathematics::MathsHelper::Clamp(y, min, max);
                    z = mathematics::MathsHelper::Clamp(z, min, max);
                }

                /// Cross takes the area of a parallelogram (or square) formed by two vectors
                /// e.g. square area formed by (2,0,0) and (0,3,0) has cross 2x3=6
                /// If first vector is to the right of the second (i.e. anti-clockwise from 1 to 2) then cross is +ve
                /// If first vector is to the left of the second (i.e. clockwise from 1 to 2) then cross is -ve
                /// A new vector is formed with length of this calculated area with direction perpendicular to the original vectors.
                /// Right hand rule applies where Index finger is first vector, Middle finger is second vector and Thumb is the resulting Cross.
                Vector3<T> Cross(const Vector3<T>& other) const {
                    return {
                        (y * other.z) - (other.y * z),
                        (z * other.x) - (other.z * x),
                        (x * other.y) - (other.x * y)
                    };
                }

                /// Dot product is the projection of the second vector onto the first
                /// Positive result means they are in the same direction (to some degree)
                /// 0 means they are perpendicular
                /// Negative result means they are in opposite directions (to some degree)
                float Dot(const Vector3<T>& other) const {
                    return (x * other.x) + (y * other.y) + (z * other.z);
                }

                bool Equals(const Vector3<T>& right) const { 
                    return *this == right; 
                }

                Vector3<T> Divide(T factor) const { 
                    return *this / factor; 
                }

                float Length() const {
                    return mathematics::MathsHelper::SquareRoot((x * x) + (y * y) + (z * z));
                }

                Vector3<T> Multiply(const Vector3<T>& right) const { 
                    return *this * right; 
                }

                Vector3<T> Multiply(T factor) const { 
                    return *this * factor; 
                }

                void Normalise() {
                    auto magnitude = Length();

                    if (magnitude != 0.0f) {
                        x /= magnitude;
                        y /= magnitude;
                        z /= magnitude;
                    }
                }

                Vector3<T> Subtract(const Vector3<T>& other) const { 
                    return *this - other; 
                }

                std::string ToString() const
                {
                    return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
                }

            public:
                static Vector3<T> Abs(const Vector3<T>& point) {
                    return Vector3<T>(mathematics::MathsHelper::Absolute(point.x), mathematics::MathsHelper::Absolute(point.y), mathematics::MathsHelper::Absolute(point.z));
                }

                static Vector3<T> Ceil(const Vector3<T>& point) {
                    return Vector3<T>(mathematics::MathsHelper::Ceiling(point.x), mathematics::MathsHelper::Ceiling(point.y), mathematics::MathsHelper::Ceiling(point.z));
                }

                static Vector3<T> Floor(const Vector3<T>& point) {
                    return Vector3<T>(mathematics::MathsHelper::Floor(point.x), mathematics::MathsHelper::Floor(point.y), mathematics::MathsHelper::Floor(point.z));
                }

                static Vector3<T> CreateInverseOf(const Vector3<T>& vector)
                {
                    return { -vector.x, -vector.y, -vector.z };
                }

                static Vector3<T> CreateReflectioneOf(const Vector3<T>& incident, const Vector3<T>& normal)
                {
                    return incident - 2.0f * normal.Dot(incident) * normal;
                }

                static Vector3<T> CreateRotationDegreesFrom(const Vector3<T>& direction)
                {
                    // NOTE: Can't really determine roll from a direction, so assume 0.0
                    Vector3<T> result;
                    result.yaw = static_cast<T>(mathematics::MathsHelper::RadiansToDegrees(mathematics::MathsHelper::ArcTangent(static_cast<float>(direction.x), static_cast<float>(direction.z))));
                    result.pitch = static_cast<T>(mathematics::MathsHelper::RadiansToDegrees(mathematics::MathsHelper::ArcSine(static_cast<float>(-direction.y))));
                    result.roll = static_cast<T>(0);

                    return result;
                }

                // Returns vector0 at t == 0, vector1 at t == 1, and linearly interpolates between them at other values of t.
                static Vector3<T> Interpolate(T delta0to1, const Vector3<T>& vector0, const Vector3<T>& vector1) 
                {
                    return (static_cast<T>(1) - delta0to1) * vector0 + delta0to1 * vector1;
                }

            public:
                friend bool operator==(const Vector3<T>& left, const Vector3<T>& right) {
                    return left.x == right.x && left.y == right.y && left.z == right.z;
                }

                friend bool operator!=(const Vector3<T>& left, const Vector3<T>& right) {
                    return !(left == right);
                }

                friend Vector3<T> operator+(const Vector3<T>& left, const Vector3<T> right) {
                    return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
                }

                friend Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right) {
                    return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
                }

                friend Vector3<T> operator*(const Vector3<T>& left, const Vector3<T>& right) {
                    return Vector3<T>(left.x * right.x, left.y * right.y, left.z * right.z);
                }

                friend Vector3<T> operator/(const Vector3<T>& left, const Vector3<T>& right) {
                    auto zero = static_cast<T>(0);
                    return Vector3<T>(
                        right.x == zero ? zero : left.x / right.x, 
                        right.y == zero ? zero : left.y / right.y, 
                        right.z == zero ? zero : left.z / right.z
                        );
                }

                friend Vector3<T> operator*(const Vector3<T>& vector, float factor) {
                    return Vector3<T>(vector.x * factor, vector.y * factor, vector.z * factor);
                }

                friend Vector3<T> operator*(float factor, const Vector3<T>& vector) {
                    return Vector3<T>(factor * vector.x, factor * vector.y, factor * vector.z);
                }

                friend Vector3<T> operator/(const Vector3<T>& vector, float factor) {
                    auto zero = static_cast<T>(0);
                    return factor == zero ? Vector3<T>() : Vector3<T>(vector.x / factor, vector.y / factor, vector.z / factor);
                }
            };
        }
    }
}