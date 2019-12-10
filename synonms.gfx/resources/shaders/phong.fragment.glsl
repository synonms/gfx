#version 330 core

const int MAX_LIGHTS = 1;

// Passed from vertex shader
in vec3 p_vertexNormalDirectionInWorldSpace;
in vec2 p_vertexTextureUV;
in vec3 p_vertexToCameraDirection;
in vec4 p_vertexPositionInLightSpace[MAX_LIGHTS];
in vec3 p_vertexToLightDirectionInWorldSpace[MAX_LIGHTS];
in float p_vertexToLightDistance[MAX_LIGHTS];

// Material
struct Material {
    vec4 diffuseColour;
    bool isDiffuseTextureEnabled;
    sampler2D diffuseTextureSlot;

    vec4 specularColour;
    bool isSpecularTextureEnabled;
    sampler2D specularTextureSlot;

    vec4 emissiveColour;
    bool isEmissiveTextureEnabled;
    sampler2D emissiveTextureSlot;

    float opacity;
    float shininess;
}; 

uniform Material fu_material;

struct MaterialSceneProduct {
   vec4 sceneColour; // material.emission + material.ambient * scene.ambient  
};

uniform MaterialSceneProduct fu_materialSceneProduct;

// Lights
struct Light {
    int type;		// 0 Directional, 1 Positional, 2 Spot
    bool isEnabled;
    vec3 position;
    vec3 direction;
    float spotInnerCutoffCosine;	// Convert to radians then get Cosine before passing in
    float spotOuterCutoffCosine;	// Convert to radians then get Cosine before passing in
    vec4 ambientColour;
    vec4 diffuseColour;
    vec4 specularColour;
    float intensityMultiplier;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
    sampler2D shadowMapTextureSlot;
};

uniform Light fu_lights[MAX_LIGHTS];

// Fragment shader requires a vec4 color output variable otherwise geometry renders black or white
// Can be named anything
layout(location = 0) out vec4 p_fragmentColour;

vec4 CalculateAmbient(int lightIndex, vec4 materialDiffuseColour);
vec4 CalculateDiffuse(int lightIndex, vec4 materialDiffuseColour);
vec4 CalculateSpecular(int lightIndex, vec4 materialSpecularColour);
float CalculateShadowFactor(int lightIndex);

void main()
{
    vec4 materialDiffuseColour = mix(fu_material.diffuseColour, texture(fu_material.diffuseTextureSlot, p_vertexTextureUV), fu_material.isDiffuseTextureEnabled);
    vec4 materialSpecularColour = mix(fu_material.specularColour, texture(fu_material.specularTextureSlot, p_vertexTextureUV), fu_material.isSpecularTextureEnabled);
    vec4 materialEmissiveColour = mix(fu_material.emissiveColour, texture(fu_material.emissiveTextureSlot, p_vertexTextureUV), fu_material.isEmissiveTextureEnabled);

    vec4 cumulativeLightColour = vec4(0.0);

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if (fu_lights[i].isEnabled)
        {
            vec4 ambient = CalculateAmbient(i, materialDiffuseColour);
            vec4 diffuse = CalculateDiffuse(i, materialDiffuseColour);
            vec4 specular = CalculateSpecular(i, materialSpecularColour);
            float shadowFactor = CalculateShadowFactor(i);

            // Calculate the attenuation factor (falloff over distance)
            float attenuation = 1.0 / (fu_lights[i].constantAttenuation +
                                            (fu_lights[i].linearAttenuation * p_vertexToLightDistance[i]) +
                                            (fu_lights[i].quadraticAttenuation * p_vertexToLightDistance[i] * p_vertexToLightDistance[i]));

            vec4 lightContribution = vec4(0.0);

            if(fu_lights[i].type == 1)
            {
                // Positional
                lightContribution = ambient + (diffuse * attenuation * shadowFactor) + (specular * attenuation * shadowFactor);
            } 
            else if (fu_lights[i].type == 2)
            {
                // Spot
                // Calculate angle between spot direction and spot to fragment (i.e. how far from centre of cone)
                float theta = dot(p_vertexToLightDirectionInWorldSpace[i], normalize(-fu_lights[i].direction));

                if(theta > fu_lights[i].spotOuterCutoffCosine) 
                {   
                    float epsilon = fu_lights[i].spotInnerCutoffCosine - fu_lights[i].spotOuterCutoffCosine;
                    float spotIntensity = clamp((theta - fu_lights[i].spotOuterCutoffCosine) / epsilon, 0.0, 1.0);    

                    lightContribution = ambient + (diffuse * attenuation * spotIntensity * shadowFactor) + (specular * attenuation * spotIntensity * shadowFactor);
                }
                else
                {
                    // Fragment is outside of spot cone - use ambient only
                    lightContribution = ambient;
                }
            } 
            else 
            {
                // Directional
                // Attentuation only on specular
                lightContribution = ambient + (diffuse * shadowFactor) + (specular * attenuation * shadowFactor);
            }

            cumulativeLightColour += fu_materialSceneProduct.sceneColour + lightContribution;
        }
    }

    p_fragmentColour = fu_materialSceneProduct.sceneColour + cumulativeLightColour + materialEmissiveColour;
}

vec4 CalculateAmbient(int lightIndex, vec4 materialDiffuseColour)
{
    vec4 ambientResult = materialDiffuseColour * fu_lights[lightIndex].ambientColour * fu_lights[lightIndex].intensityMultiplier;
    return clamp(ambientResult, 0.0, 1.0);
}

vec4 CalculateDiffuse(int lightIndex, vec4 materialDiffuseColour)
{
    float diffuseDot = max(dot(p_vertexNormalDirectionInWorldSpace, p_vertexToLightDirectionInWorldSpace[lightIndex]), 0.0);
    vec4 diffuseResult = materialDiffuseColour * fu_lights[lightIndex].diffuseColour * diffuseDot * fu_lights[lightIndex].intensityMultiplier;
    return clamp(diffuseResult, 0.0, 1.0);
}

vec4 CalculateSpecular(int lightIndex, vec4 materialSpecularColour)
{
    vec3 lightReflectionDirection = normalize(reflect(-p_vertexToLightDirectionInWorldSpace[lightIndex], p_vertexNormalDirectionInWorldSpace));
    float specularDot = max(dot(lightReflectionDirection, p_vertexToCameraDirection), 0.0);
    vec4 specularResult = materialSpecularColour * fu_lights[lightIndex].specularColour * pow(specularDot, 0.3 * fu_material.shininess) * fu_lights[lightIndex].intensityMultiplier;
    return clamp(specularResult, 0.0, 1.0); 
}

// 1.0 if fragment is lit, 0.0 if in shadow
float CalculateShadowFactor(int lightIndex)
{
    // Perform perspective divide to get fragment position in range [-1..1]
    vec3 projectionCoords = p_vertexPositionInLightSpace[lightIndex].xyz / p_vertexPositionInLightSpace[lightIndex].w;
    // Transform to range [0..1] to match depth buffer
    projectionCoords = projectionCoords * 0.5 + 0.5; 
    // Check if it's beyond the light's far plane
    if(projectionCoords.z > 1.0) return 1.0;

    // Sample the depth from the shadowMap texture
//    float shadowMapDepth = texture(fu_lights[lightIndex].shadowMapTextureSlot, projectionCoords.xy).r;
    // Get the depth of the fragment
    float fragmentDepth = projectionCoords.z;

    float bias = max(0.05 * (1.0 - dot(p_vertexNormalDirectionInWorldSpace, p_vertexToLightDirectionInWorldSpace[lightIndex])), 0.0025); 

    // Sample a few different depth values for a softer shadow
    float shadowFactor = 0.0;
    vec2 texelSize = 1.0 / textureSize(fu_lights[lightIndex].shadowMapTextureSlot, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(fu_lights[lightIndex].shadowMapTextureSlot, projectionCoords.xy + vec2(x, y) * texelSize).r; 
            shadowFactor += fragmentDepth - bias < pcfDepth ? 1.0 : 0.0;
        }    
    }
    shadowFactor /= 9.0;

//    return fragmentDepth - bias < shadowMapDepth ? 1.0 : 0.0;  
    return shadowFactor;
}
