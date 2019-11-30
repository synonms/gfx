#version 330 core

in vec2 p_vertexTextureUV;

uniform sampler2D fu_bufferTextureSlot;

layout(location = 0) out vec4 p_fragmentColour;
 
void main()
{
    p_fragmentColour = texture(fu_bufferTextureSlot, p_vertexTextureUV);
}
