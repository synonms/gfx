#version 330 core

const int MAX_LIGHTS = 1;
const float PI = 3.14159265359;

// Passed from vertex shader
in PIPELINE_VARS {
    mat3 tbnMatrix;
    vec2 textureUV;
    vec3 vertexNormalDirectionWorldSpace;
    vec3 vertexToCameraDirectionWorldSpace;
    vec3 vertexToLightDirectionWorldSpace[MAX_LIGHTS];
   float vertexToLightDistance[MAX_LIGHTS];
    vec4 vertexPositionInLightSpace[MAX_LIGHTS];
} pipeline_in;


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
    vec3 specularColourF0;
    bool isShadowReceiverOnly;
}; 

uniform Material fu_material;

// Lights
struct Light {
    int type;		// 0 Directional, 1 Positional, 2 Spot
    vec3 radiance;
//    vec3 position;
//    vec3 direction;
//    float spotInnerCutoffCosine;	// Convert to radians then get Cosine before passing in
//    float spotOuterCutoffCosine;	// Convert to radians then get Cosine before passing in
//    vec4 ambientColour;
//    vec4 diffuseColour;
//    vec4 specularColour;
//    float intensityMultiplier;
//    float constantAttenuation;
//    float linearAttenuation;
//    float quadraticAttenuation;
    sampler2D shadowMapTextureSlot;
};

uniform Light fu_lights[MAX_LIGHTS];

uniform samplerCube fu_cubeMapTextureSlot;

layout(location = 0) out vec4 p_fragmentColour;

vec3 FresnelSchlick(float NdotV, vec3 F0)
{
    return F0 + (vec3(1.0) - F0) * pow(1.0 - NdotV, 5.0);
}  

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float numerator   = NdotV;
    float denominator = NdotV * (1.0 - roughness) + roughness;

    return numerator / denominator;
}
  
float GeometrySmith(float NdotV, float NdotL, float roughness)
{
    float ggx1 = GeometrySchlickGGX(NdotV, roughness);
    float ggx2 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

float DistributionGGX(vec3 normalInWorldSpace, vec3 vertexToLightDirectionWorldSpace, float roughness)
{
    vec3 halfVector = normalize(normalInWorldSpace + vertexToLightDirectionWorldSpace);

    float roughness2 = roughness*roughness;
    float NdotH = max(dot(normalInWorldSpace, halfVector), 0.0);
    float NdotH2 = NdotH*NdotH;

    float numerator = roughness2;
    float denominator = (NdotH2 * (roughness2 - 1.0) + 1.0);
    denominator = PI * denominator * denominator;

    return numerator / denominator;
}

vec3 CookTorranceSpecular(vec3 fresnel, float geometryFunction, float normalDistributionFunction, float NdotV, float NdotL)
{
    vec3 numerator = fresnel * geometryFunction * normalDistributionFunction;
    float denominator = 4.0 * max(NdotV, 0.0) * max(NdotL, 0.0);

    return numerator / max(denominator, 0.001);
}

float CalculateAttentuation(int lightIndex)
{
    // Calculate the attenuation factor (falloff over distance)
    float attenuation = 1.0;

    if(fu_lights[lightIndex].type > 0)
    {
        attenuation = 1.0 / (pipeline_in.vertexToLightDistance[lightIndex] * pipeline_in.vertexToLightDistance[lightIndex]);
    } 

    return attenuation;
}

// 1.0 if fragment is lit, 0.0 if in shadow
float CalculateShadowFactor(int lightIndex, float NdotL)
{
    // Perform perspective divide to get fragment position in range [-1..1]
    vec3 projectionCoords = pipeline_in.vertexPositionInLightSpace[lightIndex].xyz / pipeline_in.vertexPositionInLightSpace[lightIndex].w;
    // Transform to range [0..1] to match depth buffer
    projectionCoords = projectionCoords * 0.5 + 0.5; 
    // Check if it's beyond the light's far plane
    if(projectionCoords.z > 1.0) return 1.0;

    // Sample the depth from the shadowMap texture
    float shadowMapDepth = texture(fu_lights[lightIndex].shadowMapTextureSlot, projectionCoords.xy).r;

    // Get the depth of the fragment
    float fragmentDepth = projectionCoords.z;

    // Shadow bias hack to prevent moire patterns
    float bias = 0.0025;//max(0.05 * (1.0 - NdotL), 0.005); 

//    return fragmentDepth - bias < shadowMapDepth ? 1.0 : 0.0;

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

    return shadowFactor;
}

void main()
{
    vec3 normalSample = mix(vec3(0.0), texture(fu_material.normalTextureSlot, pipeline_in.textureUV).rgb, fu_material.normalPresent);
    vec3 normalInWorldSpace = mix(normalize(pipeline_in.vertexNormalDirectionWorldSpace), pipeline_in.tbnMatrix * normalize(normalSample * 2.0 - 1.0), fu_material.normalPresent);  // transform normal vector to range [-1,1]

    if (fu_material.isShadowReceiverOnly)
    {

        float cumulativeShadowFactor = 0.0f;
        for (int i = 0; i < MAX_LIGHTS; ++i)
        {
            vec3 vertexToLightDirection = normalize(pipeline_in.vertexToLightDirectionWorldSpace[i]);
            float NdotL = max(dot(normalInWorldSpace, vertexToLightDirection), 0.0);
            cumulativeShadowFactor += CalculateShadowFactor(i, NdotL);
        }

        cumulativeShadowFactor /= float(MAX_LIGHTS);

        if (cumulativeShadowFactor == 1.0)
        {
            // Fully lit
            discard;
        }

        // Use to reduce jet black shadows on background - higher number = more background shows through
        float ambientFactor = 0.5;

        p_fragmentColour = vec4(0.0, 0.0, 0.0, ambientFactor - (ambientFactor * cumulativeShadowFactor));

        return;
    }


    vec3 albedoSample = texture(fu_material.albedoTextureSlot, pipeline_in.textureUV).rgb;
    vec3 metallicSample = mix(vec3(0.0), texture(fu_material.metallicTextureSlot, pipeline_in.textureUV).rgb, fu_material.metallicPresent);
    vec3 roughnessSample = mix(vec3(0.5), texture(fu_material.roughnessTextureSlot, pipeline_in.textureUV).rgb, fu_material.roughnessPresent);
    vec3 aoSample = mix(vec3(1.0), texture(fu_material.ambientOcclusionTextureSlot, pipeline_in.textureUV).rgb, fu_material.ambientOcclusionPresent);

    vec3 materialAlbedo = vec3(pow(albedoSample.r, 2.2), pow(albedoSample.g, 2.2), pow(albedoSample.b, 2.2));
    float materialMetallic = metallicSample.r;
    float materialRoughness = roughnessSample.r;
    float materialAO = aoSample.r;

    vec3 vertexToCameraDirectionWorldSpace = normalize(pipeline_in.vertexToCameraDirectionWorldSpace);
    vec3 reflectionDirectionInWorldSpace = reflect(-vertexToCameraDirectionWorldSpace, normalize(normalInWorldSpace));

    vec3 reflectionColour = texture(fu_cubeMapTextureSlot, reflectionDirectionInWorldSpace).rgb;

    float NdotV = max(dot(normalInWorldSpace, vertexToCameraDirectionWorldSpace), 0.0);

    vec3 outgoingRadiance = vec3(0.0);
    vec3 cumulativeAmbient = vec3(0.0);

    for (int i = 0; i < MAX_LIGHTS; ++i)
    {
        vec3 vertexToLightDirection = normalize(pipeline_in.vertexToLightDirectionWorldSpace[i]);

        // Calculate direction halfway between Vertex->Light and Vertex->Camera
        vec3 halfVector = normalize( + vertexToLightDirection);
        float NdotL = max(dot(normalInWorldSpace, vertexToLightDirection), 0.0);
        float LdotH = max(dot(vertexToLightDirection, halfVector), 0.0);
        float NdotH = max(dot(normalInWorldSpace, halfVector), 0.0);

        vec3 fresnel = FresnelSchlick(NdotH, fu_material.specularColourF0);
        float geometryFunction = GeometrySmith(NdotV, NdotL, materialRoughness);
        float normalDistributionFunction = DistributionGGX(normalInWorldSpace, vertexToLightDirection, materialRoughness);
        vec3 specular = CookTorranceSpecular(fresnel, geometryFunction, normalDistributionFunction, NdotV, NdotL);

        float attenuation = CalculateAttentuation(i);
        float shadowFactor = CalculateShadowFactor(i, NdotL);

        vec3 invertedFresnel = vec3(1.0) - fresnel;
        invertedFresnel *= 1.0 - materialMetallic;

        vec3 radiance = fu_lights[i].radiance * attenuation * NdotL;

        outgoingRadiance += (invertedFresnel * materialAlbedo / PI + specular) * radiance * shadowFactor;
        cumulativeAmbient = vec3(0.03) * ((invertedFresnel * materialAlbedo) + (fresnel * reflectionColour)) * materialAO;
    }

    vec3 outputColour = cumulativeAmbient + outgoingRadiance;

    // Gamma correction
    outputColour = outputColour / (outputColour + vec3(1.0));
    outputColour = pow(outputColour, vec3(1.0/2.2)); 

    p_fragmentColour = vec4(outputColour, 1.0);
}





