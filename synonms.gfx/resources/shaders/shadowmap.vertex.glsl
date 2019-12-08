#version 330 core

layout(location = 0) in vec3 va_position;

uniform mat4 vu_modelMatrix;
uniform mat4 vu_viewProjectionMatrix;

void main()
{
    gl_Position = vu_viewProjectionMatrix * vu_modelMatrix * vec4(va_position, 1.0);
}