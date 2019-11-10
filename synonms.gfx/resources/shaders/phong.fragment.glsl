#version 330 core

// Passed from vertex shader
in vec3 p_vertexNormalDirection;
in vec2 p_vertexTextureUV;
in vec3 p_vertexToCameraDirection;
in vec3 p_vertexToLightDirection;
in float p_vertexToLightDistance;

// Material
uniform vec4 fu_materialAmbientColour;
uniform vec4 fu_materialDiffuseColour;
uniform vec4 fu_materialSpecularColour;
uniform vec4 fu_materialEmissiveColour;
uniform float fu_materialShininess;
uniform bool fu_isTextureEnabled;
uniform sampler2D fu_textureSlot;

// Lights
uniform bool fu_isLightEnabled;
uniform vec3 fu_lightPosition;
uniform vec3 fu_lightAmbientColour;
uniform vec3 fu_lightDiffuseColour;
uniform vec3 fu_lightSpecularColour;
uniform float fu_ambientIntensityMultiplier;

// Fragment shader requires a vec4 color output variable otherwise geometry renders black or white
// Can be named anything
out vec4 p_fragmentColour;

void main()
{
    vec4 materialColour;

    vec4 diffuseColour = fu_materialDiffuseColour;
    diffuseColour.rgb *= diffuseColour.a;

    if (fu_isTextureEnabled)
    {
        // Sample the pixel color from the texture using the sampler at this texture coordinate location.
        // This defaults to (1.0, 1.0, 1.0, 1.0) if no valid texture bound
        vec4 textureColour = texture(fu_textureSlot, p_vertexTextureUV);
        textureColour.rgb *= textureColour.a;

        materialColour.rgb = textureColour.rgb + (diffuseColour.rgb * (1 - textureColour.a));
        materialColour.a = textureColour.a + (diffuseColour.a * (1.0 - textureColour.a));
    }
    else
    {
        materialColour = diffuseColour;
    }


    vec4 lightColour = vec4(1.0);

    if (fu_isLightEnabled)
    {
        vec3 lightAmbientColour = fu_lightAmbientColour * fu_ambientIntensityMultiplier;

        // The greater the angle between normal and direction to light, the lesser the diffuse light
        float lightDiffuseFactor = max(dot(p_vertexNormalDirection, p_vertexToLightDirection), 0.0);
        vec3 lightDiffuseColour = fu_lightDiffuseColour * lightDiffuseFactor;

        lightColour = vec4(lightAmbientColour + lightDiffuseColour, 1.0);
    }


    p_fragmentColour = materialColour * lightColour;
}