#version 330 core

const int MAX_LIGHTS = 3;

// Passed from vertex shader
in vec3 p_vertexNormalDirection;
in vec2 p_vertexTextureUV;
in vec3 p_vertexToCameraDirection;
in vec3 p_vertexToLightDirection[MAX_LIGHTS];
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
};

uniform Light fu_lights[MAX_LIGHTS];

// Fragment shader requires a vec4 color output variable otherwise geometry renders black or white
// Can be named anything
//out vec4 p_fragmentColour;

vec4 CalculateAmbient(int lightIndex, vec4 materialDiffuseColour);
vec4 CalculateDiffuse(int lightIndex, vec4 materialDiffuseColour);
vec4 CalculateSpecular(int lightIndex, vec4 materialSpecularColour);

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

            // Calculate the attenuation factor (falloff over distance)
            float attenuation = 1.0 / (fu_lights[i].constantAttenuation +
                                            (fu_lights[i].linearAttenuation * p_vertexToLightDistance[i]) +
                                            (fu_lights[i].quadraticAttenuation * p_vertexToLightDistance[i] * p_vertexToLightDistance[i]));

            cumulativeLightColour += fu_materialSceneProduct.sceneColour + ambient + diffuse + specular;
            
//			if(fu_light.type == 1)
//            {
//                // Positional
//                cumulativeLightColour = (ambientLightColour * materialDiffuseColour)
//                    + (diffuseLightColour * materialDiffuseColour * attenuation) 
//                    + (specularLightColour * materialSpecularColour * attenuation);
//            } 
//            else if (fu_light.type == 2)
//            {
//                // Spot
//                // Calculate angle between spot direction and spot to fragment (i.e. how far from centre of cone)
//                float theta = dot(p_vertexToLightDirection, normalize(-fu_light.direction));
//
//                if(theta > fu_light.spotOuterCutoffCosine) 
//                {   
//                    float epsilon = fu_light.spotInnerCutoffCosine - fu_light.spotOuterCutoffCosine;
//                    float spotIntensity = clamp((theta - fu_light.spotOuterCutoffCosine) / epsilon, 0.0, 1.0);    
//
//                    cumulativeLightColour = (ambientLightColour * materialDiffuseColour)
//                        + (diffuseLightColour * materialDiffuseColour * attenuation * spotIntensity) 
//                        + (specularLightColour * materialSpecularColour * attenuation * spotIntensity);
//                }
//                else
//                {
//                    // Fragment is outside of spot cone - use ambient only
//                    cumulativeLightColour = ambientLightColour * materialDiffuseColour;
//                }
//            } 
//            else 
//            {
//                // Directional
//                // Attentuation ignored
//                cumulativeLightColour = (ambientLightColour * materialDiffuseColour)
//                    + (diffuseLightColour * materialDiffuseColour) 
//                    + (specularLightColour * materialSpecularColour);
//            }
        }
    }

    gl_FragColor = fu_materialSceneProduct.sceneColour + cumulativeLightColour + materialEmissiveColour;
}

vec4 CalculateAmbient(int lightIndex, vec4 materialDiffuseColour)
{
    return materialDiffuseColour * fu_lights[lightIndex].ambientColour;
}

vec4 CalculateDiffuse(int lightIndex, vec4 materialDiffuseColour)
{
    float diffuseDot = max(dot(p_vertexNormalDirection, p_vertexToLightDirection[lightIndex]), 0.0);
    vec4 diffuseResult = materialDiffuseColour * fu_lights[lightIndex].diffuseColour * diffuseDot;
    return clamp(diffuseResult, 0.0, 1.0);
}

vec4 CalculateSpecular(int lightIndex, vec4 materialSpecularColour)
{
    vec3 lightReflectionDirection = normalize(reflect(-p_vertexToLightDirection[lightIndex], p_vertexNormalDirection));
    float specularDot = max(dot(lightReflectionDirection, p_vertexToCameraDirection), 0.0);
    vec4 specularResult = materialSpecularColour * fu_lights[lightIndex].specularColour * pow(specularDot, 0.3 * fu_material.shininess);
    return clamp(specularResult, 0.0, 1.0); 
}
