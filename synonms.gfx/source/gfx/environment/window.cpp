#include "window.h"

#include <iostream>

#include <glproxy\window.h>

using namespace synonms::gfx::environment;

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
    proxies::opengl::Window::Clear(proxies::opengl::enumerators::AttributeBit::ColourBuffer);
}

void Window::MakeContextCurrent()
{
    proxies::opengl::Window::MakeCurrent(_implementation->window);

    // TODO: this should be elsewhere
    proxies::opengl::Window::SetSwapInterval(1);
}

bool Window::ShouldClose()
{
    return proxies::opengl::Window::ShouldClose(_implementation->window);
}

void Window::SwapBuffers() 
{
    proxies::opengl::Window::SwapBuffers(_implementation->window);
}