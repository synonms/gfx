#version 330 core

const int MAX_LIGHTS = 1;
const float PI = 3.14159265359;

// Passed from vertex shader
in vec2 p_vertexTextureUV;

uniform vec3 fu_viewPosition;
uniform sampler2D fu_positionTextureSlot;
uniform sampler2D fu_normalTextureSlot;
uniform sampler2D fu_albedoSpecTextureSlot;

// Lights
struct Light {
    int type;		// 0 Directional, 1 Positional, 2 Spot
    bool isEnabled;
    vec3 position;
    vec3 direction;
    mat4 viewProjectionMatrix;

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

layout(location = 0) out vec4 p_fragmentColour;

float CalculateShadowFactor(int lightIndex, vec3 fragmentPosition, vec3 normalDirection, vec3 lightDirection);

vec3 AmbientBRDF(vec3 materialAmbientCoefficient, vec3 sceneAmbientIntensity, vec3 lightAmbientIntensity)
{
    return materialAmbientCoefficient * (sceneAmbientIntensity + lightAmbientIntensity);
}

vec3 DiffuseBRDF(vec3 materialDiffuseCoefficient, vec3 fragmentToLightDirection, vec3 normalDirection)
{
    return materialDiffuseCoefficient * dot(fragmentToLightDirection, normalDirection);
}

vec3 SpecularBRDF(vec3 materialSpecularCoefficient, vec3 fragmentToEyeDirection, vec3 reflectedLightDirection)
{
    return materialSpecularCoefficient * dot(fragmentToEyeDirection, reflectedLightDirection);
}

vec3 FresnelSchlick(vec3 F0, float cosTheta)
{
    return F0 + (vec3(1.0) - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 ReflectedDirection(vec3 incidentDirection, vec3 normalDirection)
{
    return normalize(reflect(incidentDirection, normalDirection));
}

void main()
{
    vec3 normalSample = texture(fu_normalTextureSlot, p_vertexTextureUV).rgb;

    if (normalSample == vec3(0.0, 0.0, 0.0))
    { 
        discard; 
    }

    vec3 positionSample = texture(fu_positionTextureSlot, p_vertexTextureUV).rgb;
    vec3 albedoSample = texture(fu_albedoSpecTextureSlot, p_vertexTextureUV).rgb;
    float specularSample = texture(fu_albedoSpecTextureSlot, p_vertexTextureUV).a;

    vec3 fragmentToEyeDirection = normalize(fu_viewPosition - positionSample);

    // then calculate lighting as usual
    vec3 lighting = albedoSample * 0.1; // hard-coded ambient component
    for(int i = 0; i < MAX_LIGHTS; ++i)
    {
        if (fu_lights[i].isEnabled)
        {
            vec3 fragmentToLightDirection = -fu_lights[i].direction;
            vec3 reflectedLightDirection = ReflectedDirection(fu_lights[i].direction, normalSample);

            if(fu_lights[i].type > 0)
            {
                fragmentToLightDirection = normalize(fu_lights[i].position - positionSample);
            }

            float shadowFactor = CalculateShadowFactor(i, positionSample, normalSample, fragmentToLightDirection);
        
            vec3 diffuse = max(dot(normalSample, fragmentToLightDirection), 0.0) * albedoSample * fu_lights[i].diffuseColour.xyz;

            lighting += diffuse * shadowFactor;
        }
    }

    p_fragmentColour = vec4(lighting, 1.0);
}

// 1.0 if fragment is lit, 0.0 if in shadow
float CalculateShadowFactor(int lightIndex, vec3 fragmentPosition, vec3 normalDirection, vec3 lightDirection)
{
    vec4 vertexPositionInLightSpace = fu_lights[lightIndex].viewProjectionMatrix * vec4(fragmentPosition, 1.0);

    // Perform perspective divide to get fragment position in range [-1..1]
    vec3 projectionCoords = vertexPositionInLightSpace.xyz / vertexPositionInLightSpace.w;
    // Transform to range [0..1] to match depth buffer
    projectionCoords = projectionCoords * 0.5 + 0.5; 
    // Check if it's beyond the light's far plane
    if(projectionCoords.z > 1.0) return 1.0;

    // Sample the depth from the shadowMap texture
//    float shadowMapDepth = texture(fu_lights[lightIndex].shadowMapTextureSlot, projectionCoords.xy).r;
    // Get the depth of the fragment
    float fragmentDepth = projectionCoords.z;

    float bias = max(0.05 * (1.0 - dot(normalDirection, lightDirection)), 0.0025); 

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

