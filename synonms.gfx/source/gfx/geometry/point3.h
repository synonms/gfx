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
            class Point3
            {
            public:
                T x;
                T y;
                T z;

            public:
                Point3(T value1 = static_cast<T>(0), T value2 = static_cast<T>(0), T value3 = static_cast<T>(0))
                    : x(value1), y(value2), z(value3)
                {
                }

                Point3(const Point3<T>& other)
                    : x(other.x), y(other.y), z(other.z)
                {
                }

                Point3(Point3<T>&& other) noexcept
                    : x(std::move(other.x)), y(std::move(other.y)), z(std::move(other.z))
                {
                }

                void operator=(const Point3<T>& other)
                {
                    x = other.x;
                    y = other.y;
                    z = other.z;
                }

                void operator=(Point3<T>&& other) noexcept
                {
                    x = std::move(other.x);
                    y = std::move(other.y);
                    z = std::move(other.z);
                }

            public:
                void operator+=(const Vector3<T>& vector)
                {
                    x += vector.x;
                    y += vector.y;
                    z += vector.z;
                }

                void operator-=(const Vector3<T>& vector)
                {
                    x -= vector.x;
                    y -= vector.y;
                    z -= vector.z;
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
                Vector3<T> VectorTo(const Point3<T>& other) const {
                    return { other.x - x, other.y - y, other.z - z };
                }

                void Clamp(float min, float max)
                {
                    x = mathematics::MathsHelper::Clamp(x, min, max);
                    y = mathematics::MathsHelper::Clamp(y, min, max);
                    z = mathematics::MathsHelper::Clamp(z, min, max);
                }

                bool Equals(const Point3<T>& right) const {
                    return *this == right;
                }

                float DistanceTo(const Point3<T>& other) const {
                    return VectorTo(other).Length();
                }

                std::string ToString() const
                {
                    return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
                }

            public:
                static Point3<T> Abs(const Point3<T>& point) {
                    return Point3<T>(mathematics::MathsHelper::Absolute(point.x), mathematics::MathsHelper::Absolute(point.y), mathematics::MathsHelper::Absolute(point.z));
                }

                static Point3<T> Ceil(const Point3<T>& point) {
                    return Point3<T>(mathematics::MathsHelper::Ceiling(point.x), mathematics::MathsHelper::Ceiling(point.y), mathematics::MathsHelper::Ceiling(point.z));
                }

                static Point3<T> Floor(const Point3<T>& point) {
                    return Point3<T>(mathematics::MathsHelper::Floor(point.x), mathematics::MathsHelper::Floor(point.y), mathematics::MathsHelper::Floor(point.z));
                }

                // Returns vector0 at t == 0, vector1 at t == 1, and linearly interpolates between them at other values of t.
                static Point3<T> Interpolate(T delta0to1, const Point3<T>& point0, const Point3<T>& point1) {
                    return (static_cast<T>(1) - delta0to1) * point0 + delta0to1 * point1;
                }

                static Point3<T> Max(const Point3<T>& point1, const Point3<T>& point2) {
                    return Point3<T>(mathematics::MathsHelper::Maximum(point1.x, point2.x), mathematics::MathsHelper::Maximum(point1.y, point2.y), mathematics::MathsHelper::Maximum(point1.z, point2.z));
                }

                static Point3<T> Min(const Point3<T>& point1, const Point3<T>& point2) {
                    return Point3<T>(mathematics::MathsHelper::Minimum(point1.x, point2.x), mathematics::MathsHelper::Minimum(point1.y, point2.y), mathematics::MathsHelper::Minimum(point1.z, point2.z));
                }

            public:
                friend bool operator==(const Point3<T>& left, const Point3<T>& right) {
                    return left.x == right.x && left.y == right.y && left.z == right.z;
                }

                friend bool operator!=(const Point3<T>& left, const Point3<T>& right) {
                    return !(left == right);
                }

                friend Point3<T> operator+(const Point3<T>& left, const Vector3<T> right) {
                    return Point3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
                }

                friend Point3<T> operator-(const Point3<T>& left, const Vector3<T> right) {
                    return Point3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
                }

                // The following methods make no conceptual sense but are useful
                friend Point3<T> operator+(const Point3<T>& left, const Point3<T> right) {
                    return Point3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
                }

                friend Point3<T> operator-(const Point3<T>& left, const Point3<T>& right) {
                    return Point3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
                }

                friend Point3<T> operator*(const Point3<T>& left, const Point3<T>& right) {
                    return Point3<T>(left.x * right.x, left.y * right.y, left.z * right.z);
                }

                friend Point3<T> operator/(const Point3<T>& left, const Point3<T>& right) {
                    auto zero = static_cast<T>(0);
                    return Point3<T>(
                        right.x == zero ? zero : left.x / right.x,
                        right.y == zero ? zero : left.y / right.y,
                        right.z == zero ? zero : left.z / right.z
                        );
                }

                friend Point3<T> operator*(const Point3<T>& point, float factor) {
                    return Point3<T>(point.x * factor, point.y * factor, point.z * factor);
                }

                friend Point3<T> operator*(float factor, const Point3<T>& point) {
                    return Point3<T>(factor * point.x, factor * point.y, factor * point.z);
                }

                friend Point3<T> operator/(const Point3<T>& point, float factor) {
                    auto zero = static_cast<T>(0);
                    return factor == zero ? Point3<T>() : Point3<T>(point.x / factor, point.y / factor, point.z / factor);
                }
            };
        }
    }
}