#include "window.h"

#include <GLFW\glfw3.h>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

Window::Window(int width, int height, const std::string& title)
{
    _window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

Window::Window(Window&& other) noexcept
    : _window(std::exchange(other._window, nullptr))
{
}

Window& Window::operator=(Window&& other) noexcept
{
    _window = std::exchange(other._window, nullptr);

    return *this;
}

Window::~Window()
{
    if (_window != nullptr) {
        glfwDestroyWindow(_window);
    }
}


int Window::GetHeight() const
{
    int width, height;

    glfwGetWindowSize(_window, &width, &height);

    return height;
}

std::tuple<int, int> Window::GetSize() const
{
    int width, height;

    glfwGetWindowSize(_window, &width, &height);

    return std::make_tuple(width, height);
}

int Window::GetWidth() const
{
    int width, height;

    glfwGetWindowSize(_window, &width, &height);

    return width;
}

void Window::MakeCurrent() const
{
    glfwMakeContextCurrent(_window);
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(_window);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(_window);
}


void Window::SetHint(WindowHintInt windowHint, int value)
{
    glfwWindowHint(static_cast<int>(windowHint), value);
}

void Window::SetHint(WindowHintString windowHint, const std::string& value)
{
    glfwWindowHintString(static_cast<int>(windowHint), value.c_str());
}

void Window::SetOpenGlContextVersion(int major, int minor)
{
    glfwWindowHint(static_cast<int>(WindowHintInt::ContextVersionMajor), major);
    glfwWindowHint(static_cast<int>(WindowHintInt::ContextVersionMinor), minor);
}

void Window::SetOpenGlProfile(enumerators::OpenGlProfile profile)
{
    glfwWindowHint(static_cast<int>(WindowHintInt::OpenGLProfile), static_cast<int>(profile));
}

void Window::SetSwapInterval(int interval)
{
    glfwSwapInterval(interval);
}

void Window::SetViewport(int lowerLeftX, int lowerLeftY, int width, int height)
{
    glViewport(lowerLeftX, lowerLeftY, width, height);
}
