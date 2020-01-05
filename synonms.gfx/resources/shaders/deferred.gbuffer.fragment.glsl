#version 330 core

in vec3 p_vertexPositionInWorldSpace;
in vec3 p_vertexNormalDirectionInWorldSpace;
in vec2 p_vertexTextureUV;
in mat3 p_tangentToWorldSpaceMatrix;

struct Material {
    sampler2D albedoTextureSlot;
    sampler2D normalTextureSlot;
    sampler2D metallicTextureSlot;
    sampler2D roughnessTextureSlot;
    sampler2D ambientOcclusionTextureSlot;
    bool albedoPresent;
    bool normalPresent;
    bool metallicPresent;
    bool roughnessPresent;
    bool ambientOcclusionPresent;
}; 

uniform Material fu_material;

layout (location = 0) out vec3 p_fragmentPosition;
layout (location = 1) out vec3 p_fragmentNormal;
layout (location = 2) out vec4 p_fragmentAlbedoSpec;

void main()
{
    // store the fragment position vector in the first gbuffer texture
    p_fragmentPosition = p_vertexPositionInWorldSpace;

    // also store the per-fragment normals into the gbuffer
    vec3 normalSample = texture(fu_material.normalTextureSlot, p_vertexTextureUV).rgb;
    vec3 normalInTangentSpace = normalize(normalSample * 2.0 - 1.0);
    vec3 normalInWorldSpace = normalize(p_tangentToWorldSpaceMatrix * normalInTangentSpace);

//    p_fragmentNormal = (adjustedNormal + 1.0) / 2.0;
    p_fragmentNormal = normalInWorldSpace;

    // and the diffuse per-fragment color
    p_fragmentAlbedoSpec.rgb = texture(fu_material.albedoTextureSlot, p_vertexTextureUV).rgb;

    // store specular intensity in gAlbedoSpec's alpha component
    p_fragmentAlbedoSpec.a = texture(fu_material.metallicTextureSlot, p_vertexTextureUV).r;
}
