#pragma once

#include <string>
#include <tuple>

namespace synonms
{
    namespace gfx
    {
        namespace proxies
        {
            namespace imgui
            {
                class Gui
                {
                public:
                    static void ApplyDarkStyle();
                    static bool Begin(const std::string& name);
                    static bool Button(const std::string& label);
                    static bool Checkbox(const std::string& label, bool& showAnotherWindow);
                    static bool CollapsingHeader(const std::string& header);
                    static bool ColourEdit3(const std::string& label, float* colorValues);
                    static void End();
                    static std::tuple<float, float> GetDisplayFramebufferScale();
                    static std::tuple<float, float> GetDisplaySize();
                    static float GetFramerate();
                    static void NewFrame();
                    static void PopItemWidth();
                    static void PushItemWidth(float width);
                    static void* Initialise(void* window, const std::string& glslVersion);
                    static void Render();
                    static void SameLine();
                    static void SetNextWindowPosition(float x, float y);
                    static void SetNextWindowSize(float width, float height);
                    static void Shutdown();
                    static bool SliderFloat(const std::string& label, float& value, float min, float max);
                    static bool SliderFloat3(const std::string& label, float* values, float min, float max);
                    static void Text(const std::string& text);
                };
            }
        }
    }
}