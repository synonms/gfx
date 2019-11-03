#pragma once

#include <memory>

namespace synonms
{
    namespace gfx
    {
        namespace environment
        {
            class Engine
            {
            public:
                Engine();
                ~Engine();

                void InitialiseExtensions();
                void PollEvents();
            };
        }
    }
}
