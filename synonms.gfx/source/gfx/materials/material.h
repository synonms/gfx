#pragma once

#include <gfx/mathematics/linear/vector4.h>
#include <gfx/materials/texture.h>

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
            //public:
            //    Material() = default;
            //    Material(const Material& other) = delete;
            //    Material(Material&& other) noexcept = default;
            //    ~Material() = default;
            //    Material& operator=(const Material& other) = delete;
            //    Material& operator=(Material&& other) noexcept = default;

            public:
                const mathematics::linear::Vector4<float>& GetAmbientColour() const { return _ambientColour; }
                const mathematics::linear::Vector4<float>& GetDiffuseColour() const { return _diffuseColour; }
                const mathematics::linear::Vector4<float>& GetSpecularColour() const { return _specularColour; }
                const mathematics::linear::Vector4<float>& GetEmissiveColour() const { return _emissiveColour; }
                float GetShininess() const { return _shininess; }
                const std::unordered_map<unsigned int, std::shared_ptr<Texture>>& GetTextures() const { return _textures; }

                Material& WithAmbientColour(const mathematics::linear::Vector4<float>& colour);
                Material& WithDiffuseColour(const mathematics::linear::Vector4<float>& colour);
                Material& WithSpecularColour(const mathematics::linear::Vector4<float>& colour);
                Material& WithEmissiveColour(const mathematics::linear::Vector4<float>& colour);
                Material& WithShininess(float shininess);    // Larger number = smaller specular highlight
                Material& WithTexture(unsigned int slot, std::shared_ptr<Texture> texture);

            public:
                static Material Create()
                {
                    return std::move(Material());
                }

            private:
                mathematics::linear::Vector4<float> _ambientColour{ 0.2f, 0.2f, 0.2f, 1.0f };
                mathematics::linear::Vector4<float> _diffuseColour{ 1.0f, 1.0f, 1.0f, 1.0f };
                mathematics::linear::Vector4<float> _specularColour{ 0.6f, 0.6f, 0.6f, 1.0f };
                mathematics::linear::Vector4<float> _emissiveColour{ 0.0f, 0.0f, 0.0f, 0.0f };
                float _shininess{ 0.5f };    // Larger number = smaller specular highlight
                std::unordered_map<unsigned int, std::shared_ptr<Texture>> _textures;
            };
        }
    }
}
