#include "window.h"

#include <iostream>

#include <glproxy\window.h>

using namespace synonms::gfx::environment;
using namespace synonms::gfx::mathematics::linear;

class Window::Implementation 
{
public:
    GLFWwindow* window;
};

Window::Window(int width, int height, const std::string& title)
{
    _implementation = std::make_unique<Window::Implementation>();

    proxies::opengl::Window::SetOpenGlContextVersion(3, 3);
    proxies::opengl::Window::SetOpenGlProfile(proxies::opengl::enumerators::OpenGlProfile::Core);

    _implementation->window = proxies::opengl::Window::Create(width, height, title);

    if (!_implementation->window)
    {
        throw std::exception("Failed to create window");
    }
}

Window::~Window()
{
}

void Window::Clear()
{
    proxies::opengl::Window::Clear(proxies::opengl::enumerators::AttributeBit::ColourBuffer 
        | proxies::opengl::enumerators::AttributeBit::DepthBuffer
        | proxies::opengl::enumerators::AttributeBit::StencilBuffer);

    // TODO - set viewport
}

void Window::EnableVsync()
{
    proxies::opengl::Window::SetSwapInterval(1);
}

void* Window::GetContext()
{
    return _implementation->window;
}

Vector2<int> Window::GetSize() const
{
    auto size = proxies::opengl::Window::GetSize(_implementation->window);

    return { std::get<0>(size), std::get<1>(size) };
}

void Window::MakeContextCurrent()
{
    proxies::opengl::Window::MakeCurrent(_implementation->window);
}

void Window::SetViewport(int lowerLeftX, int lowerLeftY, int width, int height)
{
    proxies::opengl::Window::SetViewport(lowerLeftX, lowerLeftY, width, height);
}

bool Window::ShouldClose()
{
    return proxies::opengl::Window::ShouldClose(_implementation->window);
}

void Window::SwapBuffers() 
{
    proxies::opengl::Window::SwapBuffers(_implementation->window);
}