#version 330 core
layout(location = 0) in vec3 va_position;
layout(location = 1) in vec3 va_normalDirection;
layout(location = 2) in vec2 va_textureUV;

uniform mat4 vu_projectionMatrix;
uniform mat4 vu_viewMatrix;
uniform mat4 vu_modelMatrix;
uniform mat3 vu_normalMatrix;

out vec3 p_normalDirectionInScreenSpace;

void main()
{
    gl_Position = vu_projectionMatrix * vu_viewMatrix * vu_modelMatrix * vec4(va_position, 1.0); 

//    mat3 normalMatrixViewSpace = mat3(transpose(inverse(vu_viewModelMatrix)));

    p_normalDirectionInScreenSpace = normalize(vec3(vu_projectionMatrix * vu_viewMatrix * vec4(vu_normalMatrix * va_normalDirection, 0.0)));
}
