#pragma once

#include <gfx\geometry\normal3.h>
#include <gfx\geometry\point3.h>
#include <gfx\geometry\vector3.h>

namespace synonms
{
    namespace gfx
    {
        namespace geometry
        {
            class MediumInterface
            {
            };

            class Interaction
            {
            public:
                Point3<float> p;
                Normal3<float> n;
                Vector3<float> pError;
                Vector3<float> wo;
                float time;
                MediumInterface mediumInterface;

            public:
                Interaction(const Point3<float>& p, const Normal3<float>& n, const Vector3<float>& pError, const Vector3<float>& wo, float time, const MediumInterface& mediumInterface)
                    : p(p), n(n), pError(pError), wo(wo), time(time), mediumInterface(mediumInterface) 
                {
                }

                Interaction(const Interaction& other)
                    : p(other.p), n(other.n), pError(other.pError), wo(other.wo), time(other.time), mediumInterface(other.mediumInterface)
                {
                }

                Interaction(Interaction&& other) noexcept
                    : p(std::move(other.p))
                    , n(std::move(other.n))
                    , pError(std::move(other.pError))
                    , wo(std::move(other.wo))
                    , time(std::move(other.time))
                    , mediumInterface(std::move(other.mediumInterface))
                {
                }

                void operator=(const Interaction& other)
                {
                    p = other.p;
                    n = other.n;
                    pError = other.pError;
                    wo = other.wo;
                    time = other.time;
                    mediumInterface = other.mediumInterface;
                }

                void operator=(Interaction&& other) noexcept
                {
                    p = std::move(other.p);
                    n = std::move(other.n);
                    pError = std::move(other.pError);
                    wo = std::move(other.wo);
                    time = std::move(other.time);
                    mediumInterface = std::move(other.mediumInterface);
                }

                // TODO
            };
        }
    }
}