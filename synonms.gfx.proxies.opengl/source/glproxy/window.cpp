#include "window.h"

#include <GLFW\glfw3.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

void Window::Clear(AttributeBit attributeBit)
{
    glClear(static_cast<unsigned int>(attributeBit));
}

GLFWwindow* Window::Create(int width, int height, const std::string& title)
{
    return glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

void Window::MakeCurrent(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
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

bool Window::ShouldClose(GLFWwindow* window)
{
    return glfwWindowShouldClose(window);
}

void Window::SwapBuffers(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}