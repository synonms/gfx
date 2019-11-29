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

void System::EnableDepthTesting()
{
    glEnable(GL_DEPTH_TEST);
}

void System::EnableStencilTest()
{
    glEnable(GL_STENCIL_TEST);
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

void System::SetFaceCulling(bool isCulled)
{
    if (isCulled) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }
    else {
        glDisable(GL_CULL_FACE);
    }
}

void System::Terminate()
{
    glfwTerminate();
}
