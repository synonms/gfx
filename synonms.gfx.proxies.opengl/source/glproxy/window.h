#pragma once

#include <string>
#include <tuple>

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
                    static void Clear(enumerators::AttributeBit attributeBit = enumerators::AttributeBit::ColourBuffer);
                    static GLFWwindow* Create(int width, int height, const std::string& title);
                    static int GetHeight(GLFWwindow* window);
                    static std::tuple<int, int> GetSize(GLFWwindow* window);
                    static int GetWidth(GLFWwindow* window);
                    static void MakeCurrent(GLFWwindow* window);
                    static void SetHint(enumerators::WindowHintInt windowHint, int value);
                    static void SetHint(enumerators::WindowHintString windowHint, const std::string& value);
                    static void SetOpenGlContextVersion(int major, int minor);
                    static void SetOpenGlProfile(enumerators::OpenGlProfile profile);
                    static void SetSwapInterval(int interval = 1);
                    static bool ShouldClose(GLFWwindow* window);
                    static void SwapBuffers(GLFWwindow* window);
                };
            }
        }
    }
}
