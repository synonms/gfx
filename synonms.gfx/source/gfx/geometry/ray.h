#pragma once

#include <gfx\geometry\point3.h>
#include <gfx\geometry\vector3.h>

#include <memory>
#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace geometry
        {
            class Medium;

            class Ray
            {
            public:
                Point3<float> origin;
                Vector3<float> direction;
                float maxExtent;
                float time;
                std::shared_ptr<Medium> medium;

            public:
                Ray(Point3<float> origin = Point3<float>(0.0f, 0.0f, 0.0f),
                    Vector3<float> direction = Vector3<float>(0.0f, 0.0f, 1.0f),
                    float maxExtent = 0.0f,
                    float time = 0.0f,
                    std::shared_ptr<Medium> medium = nullptr)
                    : origin(origin), direction(direction), maxExtent(maxExtent), time(time), medium(medium)
                {
                }

                Ray(const Ray& other)
                    : origin(other.origin), direction(other.direction), maxExtent(other.maxExtent), time(other.time), medium(other.medium)
                {
                }

                Ray(Ray&& other) noexcept
                    : origin(std::move(other.origin))
                    , direction(std::move(other.direction))
                    , maxExtent(std::move(other.maxExtent))
                    , time(std::move(other.time))
                    , medium(std::move(other.medium))
                {
                }

                void operator=(const Ray& other)
                {
                    origin = other.origin;
                    direction = other.direction;
                    maxExtent = other.maxExtent;
                    time = other.time;
                    medium = other.medium;
                }

                void operator=(Ray&& other) noexcept
                {
                    origin = std::move(other.origin);
                    direction = std::move(other.direction);
                    maxExtent = std::move(other.maxExtent);
                    time = std::move(other.time);
                    medium = std::move(other.medium);
                }

            public:
                Point3<float> operator()(float t) const { 
                    return (origin + direction) * t; 
                }

            public:
                std::string ToString() const
                {
                    return "Origin " + origin.ToString() + " Direction " + direction.ToString();
                }
            };
        }
    }
}