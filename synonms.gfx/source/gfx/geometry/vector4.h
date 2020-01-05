#pragma once

#include <gfx\mathematics\maths-helper.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace geometry
        {
            template <typename T>
            class Vector4
            {
            public:
                union
                {
                    T x;
                    T red;
                };
                union
                {
                    T y;
                    T green;
                };
                union
                {
                    T z;
                    T blue;
                };
                union
                {
                    T w;
                    T alpha;
                };

            public:
                Vector4(T value1 = static_cast<T>(0), T value2 = static_cast<T>(0), T value3 = static_cast<T>(0), T value4 = static_cast<T>(0))
                    : x(value1), y(value2), z(value3), w(value4)
                {
                }

                Vector4(const Vector4<T>& other)
                    : x(other.x), y(other.y), z(other.z), w(other.w)
                {
                }

                Vector4(Vector4<T>&& other) noexcept
                    : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z)), w(std::move(other.w))
                {
                }

                void operator=(const Vector4<T>& other)
                {
                    x = other.x;
                    y = other.y;
                    z = other.z;
                    w = other.w;
                }

                void operator=(Vector4<T>&& other) noexcept
                {
                    x = std::move(other.x);
                    y = std::move(other.y);
                    z = std::move(other.z);
                    w = std::move(other.w);
                }

            public:
                void operator+=(const Vector4<T>& other)
                {
                    x += other.x;
                    y += other.y;
                    z += other.z;
                    w += other.w;
                }

                void operator-=(const Vector4<T>& other)
                {
                    x -= other.x;
                    y -= other.y;
                    z -= other.z;
                    w -= other.w;
                }

                void operator*=(const Vector4<T>& other)
                {
                    x *= other.x;
                    y *= other.y;
                    z *= other.z;
                    w *= other.w;
                }

                void operator/=(const Vector4<T>& other)
                {
                    x /= other.x;
                    y /= other.y;
                    z /= other.z;
                    w /= other.w;
                }

            public:
                Vector4<T> Add(const Vector4<T>& other) const { 
                    return *this + other; 
                }

                void Clamp(float min, float max)
                {
                    x = mathematics::MathsHelper::Clamp(x, min, max);
                    y = mathematics::MathsHelper::Clamp(y, min, max);
                    z = mathematics::MathsHelper::Clamp(z, min, max);
                    w = mathematics::MathsHelper::Clamp(w, min, max);
                }

                /// Dot product is the projection of the second vector onto the first
                /// Positive result means they are in the same direction (to some degree)
                /// 0 means they are perpendicular
                /// Negative result means they are in opposite directions (to some degree)
                float Dot(const Vector4<T>& other) const {
                    return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
                }

                bool Equals(const Vector4<T>& right) const { 
                    return *this == right; 
                }

                Vector4<T> Divide(T factor) const { 
                    return *this / factor; 
                }

                float Length() const
                {
                    return mathematics::MathsHelper::SquareRoot((x * x) + (y * y) + (z * z) + (w * w));
                }

                Vector4<T> Multiply(const Vector4<T>& right) const { 
                    return *this * right; 
                }

                Vector4<T> Multiply(T factor) const { 
                    return *this * factor; 
                }

                void Normalise() {
                    auto magnitude = Length();

                    if (magnitude != 0.0f) {
                        x /= magnitude;
                        y /= magnitude;
                        z /= magnitude;
                        w /= magnitude;
                    }
                }

                Vector4<T> Subtract(const Vector4<T>& other) const { 
                    return *this - other; 
                }

                std::string ToString() const
                {
                    return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," + std::to_string(w) + ")";
                }

            public:
                friend bool operator==(const Vector4<T>& left, const Vector4<T>& right) {
                    return left.x == right.x && left.y == right.y && left.z == right.z && left.w == right.w;
                }

                friend bool operator!=(const Vector4<T>& left, const Vector4<T>& right) {
                    return !(left == right);
                }

                friend Vector4<T> operator+(const Vector4<T>& left, const Vector4<T>& right) {
                    return Vector4<T>(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
                }

                friend Vector4<T> operator-(const Vector4<T>& left, const Vector4<T>& right) {
                    return Vector4<T>(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
                }

                friend Vector4<T> operator*(const Vector4<T>& left, const Vector4<T>& right) {
                    return Vector4<T>(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
                }

                friend Vector4<T> operator/(const Vector4<T>& left, const Vector4<T>& right) {
                    auto zero = static_cast<T>(0);
                    return Vector4<T>(
                        right.x == zero ? zero : left.x / right.x, 
                        right.y == zero ? zero : left.y / right.y, 
                        right.z == zero ? zero : left.z / right.z, 
                        right.w == zero ? zero : left.w / right.w);
                }

                friend Vector4<T> operator*(const Vector4<T>& vector, T factor) {
                    return Vector4<T>(vector.x * factor, vector.y * factor, vector.z * factor, vector.w * factor);
                }

                friend Vector4<T> operator*(T factor, const Vector4<T>& vector) {
                    return Vector4<T>(factor * vector.x, factor * vector.y, factor * vector.z, factor * vector.w);
                }

                friend Vector4<T> operator/(const Vector4<T>& vector, T factor) {
                    auto zero = static_cast<T>(0);
                    return factor == zero ? Vector4<T>() : Vector4<T>(vector.x / factor, vector.y / factor, vector.z / factor, vector.w / factor);
                }
            };
        }
    }
}