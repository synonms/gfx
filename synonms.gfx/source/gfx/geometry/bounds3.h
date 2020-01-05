#pragma once

#include <gfx\enumerators\axis3.h>
#include <gfx\geometry\point3.h>
#include <gfx\geometry\ray.h>
#include <gfx\shapes\sphere.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace geometry
        {
            template <typename T>
            class Bounds3
            {
            public:
                Point3<T> minimum;
                Point3<T> maximum;

            public:
                // Set defaults to an invalid configuration
                Bounds3()
                    : minimum({ std::numeric_limits<T>::max(), std::numeric_limits<T>::max(), std::numeric_limits<T>::max() })
                    , maximum({ std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest() })
                {
                }

                Bounds3(Point3<T> point1, Point3<T> point2)
                    : minimum({ mathematics::MathsHelper::Minimum(point1.x, point2.x), mathematics::MathsHelper::Minimum(point1.y, point2.y), mathematics::MathsHelper::Minimum(point1.z, point2.z) })
                    , maximum({ mathematics::MathsHelper::Maximum(point1.x, point2.x), mathematics::MathsHelper::Maximum(point1.y, point2.y), mathematics::MathsHelper::Maximum(point1.z, point2.z) })
                {
                }

                Bounds3(Point3<T> pointToEnclose)
                    : minimum(pointToEnclose), maximum(pointToEnclose)
                {
                }

                Bounds3(const Bounds3<T>& other)
                    : minimum(other.minimum), maximum(other.maximum)
                {
                }

                Bounds3(Bounds3<T>&& other) noexcept
                    : minimum(std::move(other.minimum)), maximum(std::move(other.maximum))
                {
                }

                void operator=(const Bounds3<T>& other)
                {
                    minimum = other.minimum;
                    maximum = other.maximum;
                }

                void operator=(Bounds3<T>&& other) noexcept
                {
                    minimum = std::move(other.minimum);
                    maximum = std::move(other.maximum);
                }

                const Point3<T>& operator[](int i) const {
                    return i <= 0 ? minimum : maximum;
                }

                Point3<T>& operator[](int i) {
                    return i <= 0 ? minimum : maximum;
                }

                public:
                    shapes::Sphere<T> BoundingSphere() const {
                        auto center = Center();
                        return { center, center.DistanceTo(maximum) };
                    }

                    Point3<T> Center() const {
                        return (minimum + maximum) / static_cast<T>(2);
                    }

                    Point3<T> Corner(int corner) const {
                        return Point3<T>((*this)[(corner & 1)].x,
                            (*this)[(corner & 2) ? 1 : 0].y,
                            (*this)[(corner & 4) ? 1 : 0].z);
                    }

                    Vector3<T> Diagonal() const { 
                        return maximum - minimum; 
                    }

                    Bounds3<T> Expand(T delta) const {
                        return Bounds3<T>(minimum - Vector3<T>(delta, delta, delta), maximum + Vector3<T>(delta, delta, delta));
                    }

                    Point3<T> Interpolate(const Point3<T>& t) const {
                        return Point3<T>(
                            mathematics::MathsHelper::Interpolate(minimum.x, maximum.x, t.x),
                            mathematics::MathsHelper::Interpolate(minimum.y, maximum.y, t.y),
                            mathematics::MathsHelper::Interpolate(minimum.z, maximum.z, t.z));
                    }

                    inline bool IntersectP(const Ray& ray, float* hitt0, float* hitt1) const {
                        auto t0 = 0.0f, t1 = ray.maxExtent;
                        for (auto axisIndex = static_cast<unsigned int>(enumerators::Axis3::X); axisIndex < static_cast<unsigned int>(enumerators::Axis3::End); ++axisIndex) {
                            auto axis = static_cast<enumerators::Axis3>(axisIndex);
                            // Update interval for ith bounding box slab
                            float invRayDir = 1 / ray.direction[axis];
                            float tNear = (minimum[axis] - ray.origin[axis]) * invRayDir;
                            float tFar = (maximum[axis] - ray.origin[axis]) * invRayDir;
                            // Update parametric interval from slab intersection values
                            if (tNear > tFar) std::swap(tNear, tFar);
                            // Update tFar to ensure robust ray–bounds intersection
                            tFar *= 1 + 2 * mathematics::MathsHelper::Gamma(3);
                            t0 = tNear > t0 ? tNear : t0;
                            t1 = tFar < t1 ? tFar : t1;
                            if (t0 > t1) return false;
                        }

                        if (hitt0) *hitt0 = t0;
                        if (hitt1) *hitt1 = t1;

                        return true;
                    }

                    bool IsContaining(const Point3<T>& point) const {
                        return (point.x >= minimum.x && point.x <= maximum.x
                            && point.y >= minimum.y && point.y <= maximum.y
                            && point.z >= minimum.z && point.z <= maximum.z);
                    }

                    bool IsOverlapping(const Bounds3<T>& other) const {
                        bool x = (maximum.x >= other.minimum.x) && (minimum.x <= other.maximum.x);
                        bool y = (maximum.y >= other.minimum.y) && (minimum.y <= other.maximum.y);
                        bool z = (maximum.z >= other.minimum.z) && (minimum.z <= other.maximum.z);
                        return (x && y && z);
                    }

                    int MaximumExtent() const {
                        auto diagonal = Diagonal();
                        if (diagonal.x > diagonal.y&& diagonal.x > diagonal.z)
                            return 0;
                        else if (diagonal.y > diagonal.z)
                            return 1;
                        else
                            return 2;
                    }

                    Vector3<T> Offset(const Point3<T>& point) const {
                        Vector3<T> o = point - minimum;
                        if (maximum.x > minimum.x) o.x /= maximum.x - minimum.x;
                        if (maximum.y > minimum.y) o.y /= maximum.y - minimum.y;
                        if (maximum.z > minimum.z) o.z /= maximum.z - minimum.z;
                        return o;
                    }

                    T SurfaceArea() const {
                        auto diagonal = Diagonal();
                        return 2 * (diagonal.x * diagonal.y + diagonal.x * diagonal.z + diagonal.y * diagonal.z);
                    }

                    std::string ToString() const {
                        return "From " + minimum.ToString() + " to " + maximum.ToString();
                    }

                    T Volume() const {
                        auto diagonal = Diagonal();
                        return diagonal.x * diagonal.y * diagonal.z;
                    }

            public:
                static Bounds3<T> CreateUnion(const Bounds3<T>& bounds, const Point3<T>& point) {
                    return Bounds3<T>(
                        Point3<T>(mathematics::MathsHelper::Minimum(bounds.minimum.x, point.x), mathematics::MathsHelper::Minimum(bounds.minimum.y, point.y), mathematics::MathsHelper::Minimum(bounds.minimum.z, point.z)),
                        Point3<T>(mathematics::MathsHelper::Maximum(bounds.maximum.x, point.x), mathematics::MathsHelper::Maximum(bounds.maximum.y, point.y), mathematics::MathsHelper::Maximum(bounds.maximum.z, point.z)));
                }

                static Bounds3<T> CreateUnion(const Bounds3<T>& bounds1, const Bounds3<T>& bounds2) {
                    return Bounds3<T>(
                        Point3<T>(mathematics::MathsHelper::Minimum(bounds1.minimum.x, bounds2.minimum.x), mathematics::MathsHelper::Minimum(bounds1.minimum.y, bounds2.minimum.y), mathematics::MathsHelper::Minimum(bounds1.minimum.z, bounds2.minimum.z)),
                        Point3<T>(mathematics::MathsHelper::Maximum(bounds1.maximum.x, bounds2.maximum.x), mathematics::MathsHelper::Maximum(bounds1.maximum.y, bounds2.maximum.y), mathematics::MathsHelper::Maximum(bounds1.maximum.z, bounds2.maximum.z)));
                }

                static Bounds3<T> CreateIntersection(const Bounds3<T>& bounds1, const Bounds3<T>& bounds2) {
                    return Bounds3<T>(
                        Point3<T>(mathematics::MathsHelper::Maximum(bounds1.minimum.x, bounds2.minimum.x), mathematics::MathsHelper::Maximum(bounds1.minimum.y, bounds2.minimum.y), mathematics::MathsHelper::Maximum(bounds1.minimum.z, bounds2.minimum.z)),
                        Point3<T>(mathematics::MathsHelper::Minimum(bounds1.maximum.x, bounds2.maximum.x), mathematics::MathsHelper::Minimum(bounds1.maximum.y, bounds2.maximum.y), mathematics::MathsHelper::Minimum(bounds1.maximum.z, bounds2.maximum.z)));
                }
            };
        }
    }
}