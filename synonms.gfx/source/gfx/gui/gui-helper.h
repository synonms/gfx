#pragma once

#include <string>

namespace synonms
{
    namespace gfx
    {
        namespace gui
        {
            class GuiHelper
            {
            public:
                static void ApplyDarkStyle();
                static void DrawSampleWindow();
                static void* Initialise(void* window, const std::string& glslVersion);
                static void NewFrame();
                static void PopWindow();
                static void PushWindow(const std::string& title);
                static void Render();
                static void Shutdown();
                static void SliderFloat3(const std::string& label, float* values, float min = 0.0f, float max = 1.0f);

            private:
                static bool show_demo_window;
                static bool show_another_window;
                static float clear_color[];
            };
        }
    }
}
