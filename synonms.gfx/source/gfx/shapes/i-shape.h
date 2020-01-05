#pragma once

#include <gfx\geometry\bounds3.h>
#include <gfx\geometry\ray.h>
#include <gfx\geometry\surface-interaction.h>
#include <gfx\transforms\matrix4x4.h>

namespace synonms
{
    namespace gfx
    {
        namespace shapes
        {
            class IShape
            {
            public:
                virtual ~IShape() = default;

                transforms::Matrix4x4 ModelMatrix;

                virtual geometry::Bounds3<float> BoundsInObjectSpace() const = 0;
                virtual geometry::Bounds3<float> BoundsInWorldSpace() const = 0;
                virtual bool Intersect(const geometry::Ray& ray, float* tHit, geometry::SurfaceInteraction* isect, bool testAlphaTexture = true) const = 0;
                virtual float SurfaceArea() const = 0;
            };
        }
    }
}
