#pragma once

#include <gfx\exports.h>

#include <memory>
#include <string>

namespace synonms 
{
    namespace gfx 
    {
        namespace environment 
        {
            class Window
            {
            public:
                SYNONMS_GFX_API Window(int width = 640, int height = 480, const std::string& title = "");
                SYNONMS_GFX_API ~Window();

                SYNONMS_GFX_API void Clear();
                SYNONMS_GFX_API void MakeContextCurrent();
                SYNONMS_GFX_API bool ShouldClose();
                SYNONMS_GFX_API void SwapBuffers();

            private:
                class Implementation;
                std::unique_ptr<Implementation> _implementation;
            };
        }
    }
}
