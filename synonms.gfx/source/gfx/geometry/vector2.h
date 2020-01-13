#pragma once

#include <gfx\mathematics\maths-helper.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace geometry
        {
            template<typename T>
            class Vector2
            {
            public:
                union
                {
                    T x;
                    T width;
                    T near;
                    T u;
                };
                union
                {
                    T y;
                    T height;
                    T far;
                    T v;
                };

            public:
                Vector2(T value1 = static_cast<T>(0), T value2 = static_cast<T>(0))
                    : x(value1), y(value2) 
                {}

                Vector2(const Vector2<T>& other) 
                    : x(other.x), y(other.y) 
                {}

                Vector2(Vector2<T>&& other) noexcept 
                    : x(std::move(other.x)), y(std::move(other.y)) 
                {}

                void operator=(const Vector2<T>& other) {
                    x = other.x; 
                    y = other.y;
                }
                void operator=(Vector2<T>&& other) noexcept {
                    x = std::move(other.x); 
                    y = std::move(other.y);
                }

            public:
                void operator+=(const Vector2<T>& other) {
                    x += other.x;
                    y += other.y;
                }

                void operator-=(const Vector2<T>& other) {
                    x -= other.x;
                    y -= other.y;
                }

                void operator*=(const Vector2<T>& other) {
                    x *= other.x;
                    y *= other.y;
                }

                void operator/=(const Vector2<T>& other) {
                    x /= other.x;
                    y /= other.y;
                }

            public:
                Vector2<T> Add(const Vector2<T>& other) const { 
                    return *this + other; 
                }

                void Clamp(float min, float max)
                {
                    x = mathematics::MathsHelper::Clamp(x, min, max);
                    y = mathematics::MathsHelper::Clamp(y, min, max);
                }

                /// Dot product is the projection of the second vector onto the first
                /// Positive result means they are in the same direction (to some degree)
                /// 0 means they are perpendicular
                /// Negative result means they are in opposite directions (to some degree)
                float Dot(const Vector2<T>& other) const { 
                    return (x * other.x) + (y * other.y); 
                }

                bool Equals(const Vector2<T>& right) const { 
                    return *this == right; 
                }

                Vector2<T> Divide(T factor) const { 
                    return *this / factor; 
                }

                float Length() const {
                    return mathematics::MathsHelper::SquareRoot((x * x) + (y * y));
                }

                Vector2<T> Multiply(const Vector2<T>& right) const { 
                    return *this * right; 
                }

                Vector2<T> Multiply(T factor) const { 
                    return *this * factor; 
                }

                void Normalise() {
                    auto magnitude = Length();

                    if (magnitude != 0.0f) {
                        x /= magnitude;
                        y /= magnitude;
                    }
                }

                Vector2<T> Subtract(const Vector2<T>& other) const { 
                    return *this - other; 
                }

                std::string ToString() const
                {
                    return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
                }

            public:
                friend bool operator==(const Vector2<T>& left, const Vector2<T>& right) {
                    return left.x == right.x && left.y == right.y;
                }

                friend bool operator!=(const Vector2<T>& left, const Vector2<T>& right) {
                    return !(left == right);
                }

                friend Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right) {
                    return Vectorf(left.x + right.x, left.y + right.y);
                }

                friend Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right) {
                    return Vector2<T>(left.x - right.x, left.y - right.y);
                }

                friend Vector2<T> operator*(const Vector2<T>& left, const Vector2<T>& right) {
                    return Vector2<T>(left.x * right.x, left.y * right.y);
                }

                friend Vector2<T> operator/(const Vector2<T> left, const Vector2<T>& right) {
                    auto zero = static_cast<T>(0);
                    return Vector2<T>(
                        right.x == zero ? zero : left.x / right.x, 
                        right.y == zero ? zero : left.y / right.y
                        );
                }

                friend Vector2<T> operator*(const Vector2<T>& left, T right) {
                    return Vector2<T>(left.x * right, left.y * right);
                }

                friend Vector2<T> operator*(T factor, const Vector2<T>& vector) {
                    return Vector2<T>(factor * vector.x, factor * vector.y);
                }

                friend Vector2<T> operator/(const Vector2<T>& vector, T factor) {
                    auto zero = static_cast<T>(0);
                    return factor == zero ? Vector2<T>() : Vector2<T>(vector.x / factor, vector.y / factor);
                }
            };
        }
    }
}