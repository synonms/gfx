#pragma once

#include <gfx\geometry\point3.h>

namespace synonms
{
    namespace gfx
    {
        namespace shapes
        {
            template <typename T>
            class Sphere
            {
            public:
                geometry::Point3<T> center;
                T radius;

            public:
                Sphere(geometry::Point3<T> center = geometry::Point3<T>(), T radius = static_cast<T>(0))
                    : center(center)
                    , radius(radius)
                {
                }

                Sphere(const Sphere<T>& other)
                    : center(other.center), radius(other.radius)
                {
                }

                Sphere(Sphere<T>&& other) noexcept
                    : center(std::move(other.center)), radius(std::move(other.radius))
                {
                }

                void operator=(const Sphere<T>& other)
                {
                    center = other.center;
                    radius = other.radius;
                }

                void operator=(Sphere<T>&& other) noexcept
                {
                    center = std::move(other.center);
                    radius = std::move(other.radius);
                }
            };
        }
    }
}