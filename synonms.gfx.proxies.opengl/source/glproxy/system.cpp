#include "system.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <sstream>

using namespace synonms::gfx::proxies::opengl;
using namespace synonms::gfx::proxies::opengl::enumerators;

void System::EnableBlending()
{
    glEnable(GL_BLEND);
}

std::string System::GetVersion()
{
    std::stringstream stream;
    stream << "GL version " << glGetString(GL_VERSION);

    return stream.str();
}

bool System::Initialise()
{
    return glfwInit() == GLFW_TRUE;
}

bool System::InitialiseExtensions()
{
    return glewInit() == GLEW_OK;
}

void System::PollEvents()
{
    glfwPollEvents();
}

void System::SetBlendFunction(BlendFactor sourceFactor, BlendFactor destinationFactor)
{
    glBlendFunc(static_cast<unsigned int>(sourceFactor), static_cast<unsigned int>(destinationFactor));
}

void System::Terminate()
{
    glfwTerminate();
}
