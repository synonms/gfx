#include "error.h"

#include <GL\glew.h>
#include <glproxy\opengl-exception.h>

#include <sstream>
#include <vector>

using namespace synonms::gfx::proxies::opengl;

void Error::Clear()
{
    while (glGetError() != GL_NO_ERROR);
}

void Error::ThrowIf()
{
    std::map<unsigned int, std::string> errors;

    while (auto errorCode = glGetError())
    {
        errors[errorCode] = GetDefaultErrorMessage(errorCode);
    }

    if (errors.size() > 0)
    {
        throw OpenglException(std::move(errors));
    }
}

void Error::ThrowIf(std::map<unsigned int, std::string> expectedErrors, bool ignoreUnexpectedErrors)
{
    std::map<unsigned int, std::string> errors;

    while (auto errorCode = glGetError())
    {
        if (expectedErrors.find(errorCode) == std::end(expectedErrors))
        {
            if (!ignoreUnexpectedErrors)
            {
                errors[errorCode] = GetDefaultErrorMessage(errorCode);
            }
        }
        else
        {
            errors[errorCode] = expectedErrors[errorCode];
        }
    }

    if (errors.size() > 0)
    {
        throw OpenglException(std::move(errors));
    }
}

std::string Error::GetDefaultErrorMessage(unsigned int errorCode)
{
    switch (errorCode)
    {
    case GL_NO_ERROR:
        return "";
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.The offending command is ignored and has no other side effect than to set the error flag.";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE: A numeric argument is out of range.The offending command is ignored and has no other side effect than to set the error flag.";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.The offending command is ignored and has no other side effect than to set the error flag.";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.The offending command is ignored and has no other side effect than to set the error flag.";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
    case GL_STACK_UNDERFLOW:
        return "GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.";
    case GL_STACK_OVERFLOW:
        return "GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.";
    }

    std::stringstream stream;
    stream << "Unknown error code " << errorCode;

    return stream.str();
}