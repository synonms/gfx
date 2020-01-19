#version 330 core

in vec3 p_vertexTextureCoords;

uniform samplerCube fu_cubeMapTextureSlot;

layout(location = 0) out vec4 p_fragmentColour;

void main()
{    
    p_fragmentColour = texture(fu_cubeMapTextureSlot, p_vertexTextureCoords);
}