#pragma once

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
                    static void Clear();
                    static void ThrowIf();
                    static void ThrowIf(std::map<unsigned int, std::string> expectedErrors, bool ignoreUnexpectedErrors = false);

                private:
                    static std::string GetDefaultErrorMessage(unsigned int errorCode);
                };
            }
        }
    }
}
