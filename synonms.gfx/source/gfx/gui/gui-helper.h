#pragma once

#include <string>

#include <gfx\geometry\vector2.h>

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
                static bool CollapsingHeader(const std::string& header);
                static bool ColourEdit3(const std::string& label, float* values);
                static void DrawSampleWindow();
                static geometry::Vector2<float> GetDisplaySize();
                static geometry::Vector2<float> GetDisplayFramebufferScale();
                static void* Initialise(void* window, const std::string& glslVersion);
                static void NewFrame();
                static void PopItemWidth();
                static void PopWindow();
                static void PushItemWidth(float width);
                static void PushWindow(const std::string& title, float x, float y, float width, float height);
                static void Render();
                static void Shutdown();
                static void SliderFloat(const std::string& label, float& value, float min = 0.0f, float max = 1.0f);
                static void SliderFloat3(const std::string& label, float* values, float min = 0.0f, float max = 1.0f);
                static void Text(const std::string& text);

            private:
                static bool show_demo_window;
                static bool show_another_window;
                static float clear_color[];
            };
        }
    }
}
