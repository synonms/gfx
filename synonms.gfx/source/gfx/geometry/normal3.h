#pragma once

#include <gfx\enumerators\axis3.h>
#include <gfx\mathematics\maths-helper.h>
#include <gfx\geometry\vector3.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace geometry
        {
            template <typename T>
            class Normal3
            {
            public:
                T x;
                T y;
                T z;

            public:
                Normal3(T value1 = static_cast<T>(0), T value2 = static_cast<T>(0), T value3 = static_cast<T>(0))
                    : x(value1), y(value2), z(value3)
                {
                }

                Normal3(const Normal3<T>& other)
                    : x(other.x), y(other.y), z(other.z)
                {
                }

                Normal3(Normal3<T>&& other) noexcept
                    : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z))
                {
                }

                void operator=(const Normal3<T>& other)
                {
                    x = other.x;
                    y = other.y;
                    z = other.z;
                }

                void operator=(Normal3<T>&& other) noexcept
                {
                    x = std::move(other.x);
                    y = std::move(other.y);
                    z = std::move(other.z);
                }

            public:
                void operator+=(const Normal3<T>& other)
                {
                    x += other.x;
                    y += other.y;
                    z += other.z;
                }

                void operator-=(const Normal3<T>& other)
                {
                    x -= other.x;
                    y -= other.y;
                    z -= other.z;
                }

                void operator*=(const Normal3<T>& other)
                {
                    x *= other.x;
                    y *= other.y;
                    z *= other.z;
                }

                void operator/=(const Normal3<T>& other)
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
                /// Dot product is the projection of the second vector onto the first
                /// Positive result means they are in the same direction (to some degree)
                /// 0 means they are perpendicular
                /// Negative result means they are in opposite directions (to some degree)
                float Dot(const Normal3<T>& other) const {
                    return (x * other.x) + (y * other.y) + (z * other.z);
                }

                float Dot(const Vector3<T>& vector) const {
                    return (x * vector.x) + (y * vector.y) + (z * vector.z);
                }

                bool Equals(const Normal3<T>& right) const {
                    return *this == right;
                }

                float Length() const {
                    return mathematics::MathsHelper::SquareRoot((x * x) + (y * y) + (z * z));
                }

                void Normalise() {
                    auto magnitude = Length();

                    if (magnitude != 0.0f) {
                        x /= magnitude;
                        y /= magnitude;
                        z /= magnitude;
                    }
                }

                std::string ToString() const
                {
                    return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
                }

            public:
                static Vector3<T> CreateInverseOf(const Normal3<T>& normal)
                {
                    return { -normal.x, -normal - y, -normal.z };
                }

                static Normal3<T> CreateForwardFacing(const Normal3<T>& normal, const Vector3<T>& vector)
                {
                    return (normal.Dot(vector) < 0.0f) ? CreateInverseOf(normal) : normal;
                }

            public:
                friend bool operator==(const Normal3<T>& left, const Normal3<T>& right) {
                    return left.x == right.x && left.y == right.y && left.z == right.z;
                }

                friend bool operator!=(const Normal3<T>& left, const Normal3<T>& right) {
                    return !(left == right);
                }

                friend Normal3<T> operator+(const Normal3<T>& left, const Normal3<T> right) {
                    return Normal3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
                }

                friend Normal3<T> operator-(const Normal3<T>& left, const Normal3<T>& right) {
                    return Normal3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
                }

                friend Normal3<T> operator*(const Normal3<T>& left, const Normal3<T>& right) {
                    return Normal3<T>(left.x * right.x, left.y * right.y, left.z * right.z);
                }

                friend Normal3<T> operator/(const Normal3<T>& left, const Normal3<T>& right) {
                    auto zero = static_cast<T>(0);
                    return Normal3<T>(
                        right.x == zero ? zero : left.x / right.x,
                        right.y == zero ? zero : left.y / right.y,
                        right.z == zero ? zero : left.z / right.z
                        );
                }

                friend Normal3<T> operator*(const Normal3<T>& normal, float factor) {
                    return Normal3<T>(normal.x * factor, normal.y * factor, normal.z * factor);
                }

                friend Normal3<T> operator*(float factor, const Normal3<T>& normal) {
                    return Normal3<T>(factor * normal.x, factor * normal.y, factor * normal.z);
                }

                friend Normal3<T> operator/(const Normal3<T>& normal, float factor) {
                    auto zero = static_cast<T>(0);
                    return factor == zero ? Normal3<T>() : Normal3<T>(normal.x / factor, normal.y / factor, normal.z / factor);
                }
            };
        }
    }
}