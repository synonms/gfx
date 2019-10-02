#version 330 core

layout(location = 0) out vec4 colour;

uniform vec4 u_colour;
uniform sampler2D u_textureSlot;

in vec2 v_textureUV;

void main()
{
    vec4 texColour = texture(u_textureSlot, v_textureUV);
    colour = texColour;
}