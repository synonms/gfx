#pragma once

#include <gfx\geometry\interaction.h>

namespace synonms
{
    namespace gfx
    {
        namespace geometry
        {
            class SurfaceInteraction : public Interaction
            {
            public:
                SurfaceInteraction(const Point3<float>& p, const Normal3<float>& n, const Vector3<float>& pError, const Vector3<float>& wo, float time, const MediumInterface& mediumInterface)
                    : Interaction(p, n, pError, wo, time, mediumInterface)
                {
                }

                // TODO
            };
        }
    }
}