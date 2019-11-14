#version 330 core

// Passed from vertex shader
in vec3 p_vertexNormalDirection;
in vec2 p_vertexTextureUV;
in vec3 p_vertexToCameraDirection;
in vec3 p_vertexToLightDirection;
in float p_vertexToLightDistance;

// Material
struct Material {
    vec3 ambientColour;
    vec3 diffuseColour;
    vec3 specularColour;
    vec3 emissiveColour;
    float opacity;
    float shininess;
}; 

uniform Material fu_material;

uniform bool fu_isTextureEnabled;
uniform sampler2D fu_textureSlot;

// Lights
struct Light {
    bool isEnabled;
    vec3 position;
    vec3 ambientColour;
    vec3 diffuseColour;
    vec3 specularColour;
    float intensityMultiplier;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

uniform Light fu_light;

// Fragment shader requires a vec4 color output variable otherwise geometry renders black or white
// Can be named anything
out vec4 p_fragmentColour;

void main()
{
    vec4 materialColour;

    if (fu_isTextureEnabled)
    {
        // Sample the pixel color from the texture using the sampler at this texture coordinate location.
        // This defaults to (1.0, 1.0, 1.0, 1.0) if no valid texture bound
        materialColour = texture(fu_textureSlot, p_vertexTextureUV);
    }
    else
    {
        materialColour = vec4(fu_material.diffuseColour, fu_material.opacity);
    }


    vec4 litColour = materialColour;

    if (fu_light.isEnabled)
    {
        // ambient
        vec3 ambientResult = fu_light.ambientColour * fu_material.ambientColour;
    
        // diffuse 
        float diffuseFactor = max(dot(p_vertexNormalDirection, p_vertexToLightDirection), 0.0);
        vec3 diffuseResult = fu_light.diffuseColour * (diffuseFactor * fu_material.diffuseColour);
    
        // specular
        vec3 lightReflectionDirection = normalize(reflect(-p_vertexToLightDirection, p_vertexNormalDirection));
        float specularFactor = pow(max(dot(p_vertexToCameraDirection, lightReflectionDirection), 0.0), fu_material.shininess);
        vec3 specularResult = fu_light.specularColour * (specularFactor * fu_material.specularColour);  

        // Calculate the attenuation factor (falloff over distance)
        float attenuation = 1.0 / (fu_light.constantAttenuation +
                                        (fu_light.linearAttenuation * p_vertexToLightDistance) +
                                        (fu_light.quadraticAttenuation * p_vertexToLightDistance * p_vertexToLightDistance));
        
        vec3 lightResult = ambientResult + diffuseResult + specularResult;

        litColour = vec4(lightResult * attenuation, 1.0);
    }

    // Add on the material emissive (self illumination)
    p_fragmentColour = vec4(fu_material.emissiveColour, 1.0) + litColour;
}