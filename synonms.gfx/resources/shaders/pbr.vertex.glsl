#version 330 core

const int MAX_LIGHTS = 1;

// Vertex Attributes - unique per vertex
layout(location = 0) in vec3 va_position;
layout(location = 1) in vec3 va_normalDirection;
layout(location = 2) in vec2 va_textureUV;
layout(location = 3) in vec3 va_tangentDirection;

// Uniforms - global
uniform mat4 vu_modelMatrix;
uniform mat4 vu_viewMatrix;
uniform mat4 vu_projectionMatrix;
uniform mat3 vu_normalMatrix;

struct Camera
{
    vec3 position;
};

uniform Camera vu_camera;

// Lights
struct Light {
     int type;    // 0 Directional, 1 Positional, 2 Spot
    vec3 position;
    vec3 direction;
    mat4 viewProjectionMatrix;
};

uniform Light vu_lights[MAX_LIGHTS];

out PIPELINE_VARS {
    mat3 tbnMatrix;
    vec2 textureUV;
    vec3 vertexNormalDirectionWorldSpace;
    vec3 vertexToCameraDirectionWorldSpace;
    vec3 vertexToLightDirectionWorldSpace[MAX_LIGHTS];
   float vertexToLightDistance[MAX_LIGHTS];
    vec4 vertexPositionInLightSpace[MAX_LIGHTS];
} pipeline_out;

void main()
{
    vec4 vertexPositionInWorldSpace = vu_modelMatrix * vec4(va_position, 1.0f);     // w of 1.0f denotes position rather than direction
    vec4 vertexPositionEyeSpace = vu_viewMatrix * vertexPositionInWorldSpace;       // Effectively moves camera to 0,0,0
    vec4 vertexPositionScreenSpace = vu_projectionMatrix * vertexPositionEyeSpace;

    vec3 normalInWorldSpace = normalize(vu_normalMatrix * va_normalDirection);
    vec3 tangentInWorldSpace = normalize(vu_normalMatrix * va_tangentDirection);
    vec3 binormalInWorldSpace = normalize(vu_normalMatrix * cross(va_normalDirection, va_tangentDirection));
    pipeline_out.tbnMatrix = mat3(tangentInWorldSpace, binormalInWorldSpace, normalInWorldSpace);

    pipeline_out.textureUV = va_textureUV;
    pipeline_out.vertexNormalDirectionWorldSpace = normalInWorldSpace;
    pipeline_out.vertexToCameraDirectionWorldSpace = vu_camera.position - vertexPositionInWorldSpace.xyz;

    for (int i = 0; i < MAX_LIGHTS; i++)
    {
        pipeline_out.vertexPositionInLightSpace[i] = vu_lights[i].viewProjectionMatrix * vertexPositionInWorldSpace;

        if(vu_lights[i].type == 0)
        {
            // Directional
            pipeline_out.vertexToLightDirectionWorldSpace[i] = normalize(-vu_lights[i].direction);
            pipeline_out.vertexToLightDistance[i] = 0;
        }
        else
        {
            // Positional or Spot
            // Calculate the direction and distance from the vertex to each light (lights are already in world space)
            vec3 vertexToLight = vu_lights[i].position - vertexPositionInWorldSpace.xyz;
            pipeline_out.vertexToLightDistance[i] = length(vertexToLight);
            pipeline_out.vertexToLightDirectionWorldSpace[i] = normalize(vertexToLight);
        }
    }

    gl_Position = vertexPositionScreenSpace;
}
