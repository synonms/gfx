#pragma once

#include <glproxy\glproxy-exports.h>

#include <exception>
#include <string>
#include <map>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class OpenglException : std::exception
                {
                public:
                    GLPROXY_API OpenglException(const std::map<unsigned int, std::string>& errors);
                    GLPROXY_API const std::map<unsigned int, std::string>& Errors() const { return _errors; }
                private:
                    std::map<unsigned int, std::string> _errors;
                };
            }
        }
    }
}
