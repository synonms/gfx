#pragma once

#include <gfx\exports.h>

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
                SYNONMS_GFX_API Engine();
                SYNONMS_GFX_API ~Engine();

                SYNONMS_GFX_API void InitialiseExtensions();
                SYNONMS_GFX_API void PollEvents();
            };
        }
    }
}
