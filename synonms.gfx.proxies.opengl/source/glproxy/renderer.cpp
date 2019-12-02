#include "renderer.h"

#include <GLFW\glfw3.h>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

void Renderer::Clear(AttributeBit attributeBit)
{
    glClear(static_cast<unsigned int>(attributeBit));
}

void Renderer::ClearColour(float red, float green, float blue, float alpha)
{
    glClearColor(red, green, blue, alpha);
}

void Renderer::ClearDepth(double value)
{
    glClearDepth(value);
}

void Renderer::ClearStencil(int value)
{
    glClearStencil(value);
}
