#include "state-manager.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <sstream>

using namespace synonms::gfx::api::opengl;
using namespace synonms::gfx::api::opengl::enumerators;

void StateManager::DisableBlending()
{
    glDisable(GL_BLEND);
}

void StateManager::DisableDepthTesting()
{
    glDisable(GL_DEPTH_TEST);
}

void StateManager::DisableStencilTest()
{
    glDisable(GL_STENCIL_TEST);
}

void StateManager::EnableBlending()
{
    glEnable(GL_BLEND);
}

void StateManager::EnableDepthTesting()
{
    glEnable(GL_DEPTH_TEST);
}

void StateManager::EnableStencilTest()
{
    glEnable(GL_STENCIL_TEST);
}

std::string StateManager::GetVersion()
{
    std::stringstream stream;
    stream << "GL version " << glGetString(GL_VERSION);

    return stream.str();
}

void StateManager::SetBlendFunction(BlendFactor sourceFactor, BlendFactor destinationFactor)
{
    glBlendFunc(static_cast<unsigned int>(sourceFactor), static_cast<unsigned int>(destinationFactor));
}

void StateManager::SetFaceCulling(bool isCulled)
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
