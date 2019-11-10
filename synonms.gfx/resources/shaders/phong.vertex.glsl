#version 330 core

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
uniform bool vu_isLightEnabled;
uniform vec3 vu_lightPosition;

// Pass to Fragment Shader
out vec3 p_vertexNormalDirection;
out vec2 p_vertexTextureUV;
out vec3 p_vertexToCameraDirection;
out vec3 p_vertexToLightDirection;
out float p_vertexToLightDistance;

void main()
{
    // Move vertex to World space (1.0f denotes position vector rather than direction)
    gl_Position = vu_modelMatrix * vec4(va_position, 1.0f);

    // Calculate the direction and distance from the vertex to each light (lights are already in world space)
    p_vertexToLightDirection = normalize(vu_lightPosition - gl_Position.xyz);
    p_vertexToLightDistance = length(p_vertexToLightDirection);

    // Move vertex to camera space (with camera at 0,0,0)
    gl_Position = vu_viewMatrix * gl_Position;

    // Calculate the direction from the vertex to camera
    p_vertexToCameraDirection = normalize(-gl_Position.xyz);

    // Move vertex to eye space
    gl_Position = vu_projectionMatrix * gl_Position;

    // Pass the other variables to the fragment shader to do it's colouring shizzle
    p_vertexTextureUV = va_textureUV;
    p_vertexNormalDirection = normalize(vu_normalMatrix * va_normalDirection);
}