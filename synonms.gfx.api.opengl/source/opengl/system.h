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
                class System
                {
                public:
                    static bool Initialise();
                    static bool InitialiseExtensions();
                    static void PollEvents();
                    static void Terminate();
                };
            }
        }
    }
}
