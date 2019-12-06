#pragma once

#include <string>
#include <tuple>

#include <opengl\enumerators\opengl-profile.h>
#include <opengl\enumerators\window-hint.h>

struct GLFWwindow;

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class Window
                {
                public:
                    Window(int width = 1920, int height = 1024, const std::string& title = "synonms gfx");
                    Window(Window&& other) noexcept;
                    Window& operator=(Window&& other) noexcept;
                    ~Window();

                    Window(const Window& other) = delete;
                    Window& operator=(const Window& other) = delete;

                public:
                    int GetHeight() const;
                    std::tuple<int, int> GetSize() const;
                    int GetWidth() const;
                    inline GLFWwindow* GetWindow() const { return _window; }
                    void MakeCurrent() const;
                    bool ShouldClose() const;
                    void SwapBuffers() const;

                public:
                    static void SetHint(enumerators::WindowHintInt windowHint, int value);
                    static void SetHint(enumerators::WindowHintString windowHint, const std::string& value);
                    static void SetOpenGlContextVersion(int major, int minor);
                    static void SetOpenGlProfile(enumerators::OpenGlProfile profile);
                    static void SetSwapInterval(int interval = 1);
                    static void SetViewport(int lowerLeftX, int lowerLeftY, int width, int height);

                private:
                    GLFWwindow* _window{ nullptr };
                };
            }
        }
    }
}
