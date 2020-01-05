#pragma once

#include <exception>
#include <string>
#include <map>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class OpenglException : std::exception
                {
                public:
                    OpenglException(const std::string& error);
                    OpenglException(const std::map<unsigned int, std::string>& errors);
                    const std::map<unsigned int, std::string>& Errors() const { return _errors; }

                private:
                    std::map<unsigned int, std::string> _errors;
                };
            }
        }
    }
}
