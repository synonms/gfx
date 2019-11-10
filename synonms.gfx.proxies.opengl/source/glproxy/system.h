#pragma once

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
                    static void EnableBlending();
                    static std::string GetVersion();
                    static bool Initialise();
                    static bool InitialiseExtensions();
                    static void PollEvents();
                    static void SetBlendFunction(enumerators::BlendFactor sourceFactor, enumerators::BlendFactor destinationFactor);
                    static void SetFaceCulling(bool isCulled);
                    static void Terminate();
                };
            }
        }
    }
}
