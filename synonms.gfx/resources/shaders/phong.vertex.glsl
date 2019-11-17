#version 330 core

const int MAX_LIGHTS = 3;

// Vertex Attributes - unique per vertex
layout(location = 0) in vec3 va_position;
layout(location = 1) in vec3 va_normalDirection;
layout(location = 2) in vec2 va_textureUV;

// Uniforms - global
uniform mat4 vu_modelMatrix;
uniform mat4 vu_viewMatrix;
uniform mat4 vu_projectionMatrix;
uniform mat3 vu_normalMatrix;

// Lights
struct Light {
    int type;		// 0 Directional, 1 Positional, 2 Spot
    bool isEnabled;
    vec3 position;
    vec3 direction;
//    float spotInnerCutoffCosine;	// Convert to radians then get Cosine before passing in
//    float spotOuterCutoffCosine;	// Convert to radians then get Cosine before passing in
//    vec4 ambientColour;
//    vec4 diffuseColour;
//    vec4 specularColour;
//    float intensityMultiplier;
//    float constantAttenuation;
//    float linearAttenuation;
//    float quadraticAttenuation;
};

uniform Light vu_lights[MAX_LIGHTS];

// Pass to Fragment Shader
out vec3 p_vertexNormalDirection;
out vec2 p_vertexTextureUV;
out vec3 p_vertexToCameraDirection;
out vec3 p_vertexToLightDirection[MAX_LIGHTS];
out float p_vertexToLightDistance[MAX_LIGHTS];

void main()
{
    // Move vertex to World space (1.0f denotes position vector rather than direction)
    vec4 vertexPositionWorldSpace = vu_modelMatrix * vec4(va_position, 1.0f);

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        if(vu_lights[i].type == 0)
        {
            // Directional
            p_vertexToLightDirection[i] = normalize(-vu_lights[i].direction);
            p_vertexToLightDistance[i] = 0;
        } 
        else
        {
            // Positional or Spot
            // Calculate the direction and distance from the vertex to each light (lights are already in world space)
            vec3 vertexToLight = vu_lights[i].position - vertexPositionWorldSpace.xyz;
            p_vertexToLightDistance[i] = length(vertexToLight);
            p_vertexToLightDirection[i] = normalize(vertexToLight);
        } 
    }

    // Move vertex to eye/camera space (with camera at 0,0,0)
    vec4 vertexPositionEyeSpace = vu_viewMatrix * vertexPositionWorldSpace;

    // Calculate the direction from the vertex to camera
    p_vertexToCameraDirection = normalize(-vertexPositionEyeSpace.xyz);

    // Move vertex to screen space
    gl_Position = vu_projectionMatrix * vertexPositionEyeSpace;

    // Pass the other variables to the fragment shader to do it's colouring shizzle
    p_vertexTextureUV = va_textureUV;
    p_vertexNormalDirection = normalize(vu_normalMatrix * va_normalDirection);
}