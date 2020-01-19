#version 330 core

layout(location = 0) in vec3 va_position;

out vec3 p_vertexTextureCoords;

uniform mat4 vu_sceneRotationMatrix;
uniform mat4 vu_projectionMatrix;

void main()
{
    p_vertexTextureCoords = -va_position;

    gl_Position = vu_projectionMatrix * vu_sceneRotationMatrix * vec4(va_position, 1.0);
} 
