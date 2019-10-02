#pragma once

#include <glproxy\glproxy-exports.h>

#include <map>
#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class Error
                {
                public:
                    GLPROXY_API static void Clear();
                    GLPROXY_API static void ThrowIf();
                    GLPROXY_API static void ThrowIf(std::map<unsigned int, std::string> expectedErrors, bool ignoreUnexpectedErrors = false);

                private:
                    static std::string GetDefaultErrorMessage(unsigned int errorCode);
                };
            }
        }
    }
}
