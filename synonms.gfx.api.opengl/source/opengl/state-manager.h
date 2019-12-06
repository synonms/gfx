#pragma once

#include <opengl\enumerators\blend-factor.h>

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace api
        {
            namespace opengl
            {
                class StateManager
                {
                public:
                    static void DisableBlending();
                    static void DisableDepthTesting();
                    static void DisableStencilTest();
                    static void EnableBlending();
                    static void EnableDepthTesting();
                    static void EnableStencilTest();
                    static std::string GetVersion();
                    static void SetBlendFunction(enumerators::BlendFactor sourceFactor, enumerators::BlendFactor destinationFactor);
                    static void SetFaceCulling(bool isCulled);
                };
            }
        }
    }
}
