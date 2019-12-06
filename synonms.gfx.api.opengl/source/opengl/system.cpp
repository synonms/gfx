#include "system.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <sstream>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

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

void System::Terminate()
{
    glfwTerminate();
}
