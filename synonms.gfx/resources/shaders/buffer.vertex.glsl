#version 330 core

// Vertex Attributes - unique per vertex
layout(location = 0) in vec3 va_position;
layout(location = 1) in vec3 va_normalDirection;
layout(location = 2) in vec2 va_textureUV;

out vec2 p_vertexTextureUV;

void main()
{
    gl_Position = vec4(va_position.xy, 0.0f, 1.0f);

    p_vertexTextureUV = va_textureUV;
}