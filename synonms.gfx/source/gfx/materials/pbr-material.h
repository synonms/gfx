#pragma once

#include <gfx\geometry\vector3.h>
#include <opengl\texture.h>

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace materials
        {
            class PBRMaterial
            {
            public:
                std::shared_ptr<api::opengl::Texture> Albedo{ nullptr };
                std::shared_ptr<api::opengl::Texture> Normal{ nullptr };
                std::shared_ptr<api::opengl::Texture> Metallic{ nullptr };
                std::shared_ptr<api::opengl::Texture> Roughness{ nullptr };
                std::shared_ptr<api::opengl::Texture> AmbientOcclusion{ nullptr };

                // F0 = surface reflection at zero incidence 
                // This is how much the surface reflects if looking directly at the surface
                // It varies per material and is tinted on metals as we find in large material databases
                // Dielectrics are monochrome and have low values
                geometry::Vector3<float> SpecularColourF0{0.04f, 0.04f, 0.04f};

                bool isShadowReceiverOnly{ false };
            };
        }
    }
}
