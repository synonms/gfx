#include "material.h"

using namespace synonms::gfx::enumerators;
using namespace synonms::gfx::materials;
using namespace synonms::gfx::mathematics::linear;

void Material::ActivateTexture(TextureSlot slot) const
{
    if (_textures.find(slot) != std::end(_textures)) {
        _textures.at(slot)->Bind(slot);
    }
}

Material& Material::WithDiffuseColour(const Vector4<float>& colour)
{
    diffuseColour = colour;

    return *this;
}

Material& Material::WithSpecularColour(const Vector4<float>& colour)
{
    specularColour = colour;

    return *this;
}

Material& Material::WithEmissiveColour(const Vector4<float>& colour)
{
    emissiveColour = colour;

    return *this;
}

Material& Material::WithShininess(float materialShininess)
{
    shininess = materialShininess;

    return *this;
}

Material& Material::WithTexture(TextureSlot slot, std::shared_ptr<Texture> texture)
{
    if (_textures.find(slot) != std::end(_textures)) {
        _textures.erase(slot);
    }

    _textures.insert(std::make_pair(slot, texture));
    _textures.at(slot)->Bind(slot);

    return *this;
}
