#version 330 core

const int MAX_LIGHTS = 1;

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
    int type;    // 0 Directional, 1 Positional, 2 Spot
    vec3 position;
    vec3 direction;
    mat4 viewProjectionMatrix;
};

uniform Light vu_lights[MAX_LIGHTS];

// Pass to Fragment Shader
out vec3 p_vertexNormalDirectionInWorldSpace;
out vec2 p_vertexTextureUV;
out vec3 p_vertexToCameraDirection;
out vec4 p_vertexPositionInLightSpace[MAX_LIGHTS];
out vec3 p_vertexToLightDirectionInWorldSpace[MAX_LIGHTS];
out float p_vertexToLightDistance[MAX_LIGHTS];

void main()
{
    // Move vertex to World space (1.0f denotes position vector rather than direction)
    vec4 vertexPositionInWorldSpace = vu_modelMatrix * vec4(va_position, 1.0f);
    p_vertexNormalDirectionInWorldSpace = normalize(vu_normalMatrix * va_normalDirection);

    //    mat3 normalMatrixWorldSpace = mat3(transpose(inverse(vu_modelMatrix)));

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        p_vertexPositionInLightSpace[i] = vu_lights[i].viewProjectionMatrix * vertexPositionInWorldSpace;

        if(vu_lights[i].type == 0)
        {
            // Directional
            p_vertexToLightDirectionInWorldSpace[i] = normalize(-vu_lights[i].direction);
            p_vertexToLightDistance[i] = 0;
        }
        else
        {
            // Positional or Spot
            // Calculate the direction and distance from the vertex to each light (lights are already in world space)
            vec3 vertexToLight = vu_lights[i].position - vertexPositionInWorldSpace.xyz;
            p_vertexToLightDistance[i] = length(vertexToLight);
            p_vertexToLightDirectionInWorldSpace[i] = normalize(vertexToLight);
        }
    }

    // Move vertex to eye/camera space (with camera at 0,0,0)
    vec4 vertexPositionEyeSpace = vu_viewMatrix * vertexPositionInWorldSpace;

    // Calculate the direction from the vertex to camera
    p_vertexToCameraDirection = normalize(-vertexPositionEyeSpace.xyz);

    // Move vertex to screen space
    gl_Position = vu_projectionMatrix * vertexPositionEyeSpace;

    // Pass the other variables to the fragment shader to do it's colouring shizzle
    p_vertexTextureUV = va_textureUV;
}