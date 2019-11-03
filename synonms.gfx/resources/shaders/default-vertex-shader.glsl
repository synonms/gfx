#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 textureUV;

out vec2 v_textureUV;

uniform mat4 u_modelViewProjection;

void main()
{
    gl_Position = u_modelViewProjection * position;
    v_textureUV = textureUV;
}