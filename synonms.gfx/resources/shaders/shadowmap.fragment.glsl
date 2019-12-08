#version 330 core 

layout(location = 0) out vec4 p_fragmentColour;

uniform bool fu_isOrthographic;
uniform float fu_nearPlane;
uniform float fu_farPlane;

float LineariseDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * fu_nearPlane * fu_farPlane) / (fu_farPlane + fu_nearPlane - z * (fu_farPlane - fu_nearPlane));
}

void main()
{
    // This happens implicitly so is not required
//    gl_FragDepth = gl_FragCoord.z;

    if (fu_isOrthographic)
    {
        p_fragmentColour = vec4(vec3(gl_FragCoord.z), 1.0);
    }
    else
    {
        p_fragmentColour = vec4(vec3(LineariseDepth(gl_FragCoord.z) / fu_farPlane), 1.0);
    }
}
