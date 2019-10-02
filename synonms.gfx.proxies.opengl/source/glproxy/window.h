#pragma once

#include <glproxy\glproxy-exports.h>

#include <string>

#include <glproxy\enumerators\attribute-bit.h>
#include <glproxy\enumerators\opengl-profile.h>
#include <glproxy\enumerators\window-hint.h>

struct GLFWwindow;

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class Window
                {
                public:
                    GLPROXY_API static void Clear(enumerators::AttributeBit attributeBit = enumerators::AttributeBit::ColourBuffer);
                    GLPROXY_API static GLFWwindow* Create(int width, int height, const std::string& title);
                    GLPROXY_API static void MakeCurrent(GLFWwindow* window);
                    GLPROXY_API static void SetHint(enumerators::WindowHintInt windowHint, int value);
                    GLPROXY_API static void SetHint(enumerators::WindowHintString windowHint, const std::string& value);
                    GLPROXY_API static void SetOpenGlContextVersion(int major, int minor);
                    GLPROXY_API static void SetOpenGlProfile(enumerators::OpenGlProfile profile);
                    GLPROXY_API static void SetSwapInterval(int interval = 1);
                    GLPROXY_API static bool ShouldClose(GLFWwindow* window);
                    GLPROXY_API static void SwapBuffers(GLFWwindow* window);
                };
            }
        }
    }
}
