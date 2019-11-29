#version 330 core

layout(location = 0) in vec3 va_position;

uniform mat4 vu_modelViewProjectionMatrix;

void main()
{
    gl_Position = vu_modelViewProjectionMatrix * vec4(va_position, 1.0f);
}