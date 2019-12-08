#pragma once

#include <gfx/mathematics/linear/vector3.h>
#include <gfx/mathematics/linear/vector4.h>

#include <opengl\texture.h>

#include <unordered_map>
#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace materials
        {
            class Material
            {
            public:
                mathematics::linear::Vector4<float> diffuseColour{ 1.0f, 1.0f, 1.0f, 1.0f };
                mathematics::linear::Vector4<float> specularColour{ 0.5f, 0.5f, 0.5f, 1.0f };
                mathematics::linear::Vector4<float> emissiveColour{ 0.0f, 0.0f, 0.0f, 1.0f };
                float shininess{ 1.0f };    // Larger number = smaller specular highlight

                inline bool IsTextureEnabled(unsigned int slot) const 
                {
                    return _textures.find(slot) != std::end(_textures);
                }

                void ActivateTexture(unsigned int slot) const;

                Material& WithDiffuseColour(const mathematics::linear::Vector4<float>& colour);
                Material& WithSpecularColour(const mathematics::linear::Vector4<float>& colour);
                Material& WithEmissiveColour(const mathematics::linear::Vector4<float>& colour);
                Material& WithShininess(float shininess);    // Larger number = smaller specular highlight
                Material& WithTexture(unsigned int slot, std::shared_ptr<api::opengl::Texture> texture);

            public:
                static Material Create()
                {
                    return std::move(Material());
                }

            private:
                std::unordered_map<unsigned int, std::shared_ptr<api::opengl::Texture>> _textures;
            };
        }
    }
}
