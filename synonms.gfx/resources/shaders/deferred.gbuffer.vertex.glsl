#version 330 core

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

// Pass to Fragment Shader
out vec3 p_vertexPositionInWorldSpace;
out vec3 p_vertexNormalDirectionInWorldSpace;
out vec2 p_vertexTextureUV;
out mat3 p_tangentToWorldSpaceMatrix;

void main()
{
//    mat3 normalMatrix = transpose(inverse(mat3(vu_modelMatrix)));

    p_vertexNormalDirectionInWorldSpace = normalize(vec3(vu_normalMatrix * va_normalDirection));
    vec3 tangentInWorldSpace = normalize(vec3(vu_normalMatrix * va_tangentDirection));
    vec3 bitangentInWorldSpace = cross(p_vertexNormalDirectionInWorldSpace, tangentInWorldSpace);

    p_tangentToWorldSpaceMatrix = mat3(tangentInWorldSpace, bitangentInWorldSpace, p_vertexNormalDirectionInWorldSpace);

    vec4 vertexPositionInWorldSpace = vu_modelMatrix * vec4(va_position, 1.0f);
    p_vertexPositionInWorldSpace = vertexPositionInWorldSpace.xyz;

    p_vertexTextureUV = va_textureUV;

    gl_Position = vu_projectionMatrix * vu_viewMatrix * vertexPositionInWorldSpace;
}