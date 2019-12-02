#pragma once

#include <memory>
#include <string>

#include <gfx\mathematics\linear\vector2.h>

namespace synonms 
{
    namespace gfx 
    {
        namespace environment 
        {
            class Window
            {
            public:
                Window(int width = 640, int height = 480, const std::string& title = "");
                ~Window();

                void EnableVsync();
                void* GetContext();
                mathematics::linear::Vector2<int> GetSize() const;
                void MakeContextCurrent();
                void SetViewport(int left, int bottom, int width, int height);
                bool ShouldClose();
                void SwapBuffers();

            private:
                class Implementation;
                std::unique_ptr<Implementation> _implementation;
            };
        }
    }
}
