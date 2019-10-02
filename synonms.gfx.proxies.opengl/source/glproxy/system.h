#pragma once

#include <glproxy\glproxy-exports.h>
#include <glproxy\enumerators\blend-factor.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace opengl
            {
                class System
                {
                public:
                    GLPROXY_API static void EnableBlending();
                    GLPROXY_API static std::string GetVersion();
                    GLPROXY_API static bool Initialise();
                    GLPROXY_API static bool InitialiseExtensions();
                    GLPROXY_API static void PollEvents();
                    GLPROXY_API static void SetBlendFunction(enumerators::BlendFactor sourceFactor, enumerators::BlendFactor destinationFactor);
                    GLPROXY_API static void Terminate();
                };
            }
        }
    }
}
