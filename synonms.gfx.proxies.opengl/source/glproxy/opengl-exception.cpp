#include "opengl-exception.h"

using namespace synonms::gfx::proxies::opengl;

OpenglException::OpenglException(const std::map<unsigned int, std::string>& errors)
    : std::exception("An OpenGL error occurred")
{
    _errors = errors;
}