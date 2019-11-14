#include "material.h"

using namespace synonms::gfx::materials;
using namespace synonms::gfx::mathematics::linear;

Material& Material::WithAmbientColour(const Vector3<float>& colour)
{
    _ambientColour = colour;

    return *this;
}

Material& Material::WithDiffuseColour(const Vector3<float>& colour)
{
    _diffuseColour = colour;

    return *this;
}

Material& Material::WithSpecularColour(const Vector3<float>& colour)
{
    _specularColour = colour;

    return *this;
}

Material& Material::WithEmissiveColour(const Vector3<float>& colour)
{
    _emissiveColour = colour;

    return *this;
}

Material& Material::WithOpacity(float opacity)
{
    _opacity = opacity;

    return *this;
}

Material& Material::WithShininess(float shininess)
{
    _shininess = shininess;

    return *this;
}

Material& Material::WithTexture(unsigned int slot, std::shared_ptr<Texture> texture)
{
    if (_textures.find(slot) != std::end(_textures)) {
        _textures.erase(slot);
    }

    _textures.insert(std::make_pair(slot, texture));
    _textures[slot]->Bind(slot);

    return *this;
}
