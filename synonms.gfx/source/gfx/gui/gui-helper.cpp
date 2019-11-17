#include "gui-helper.h"

#include <GLFW\glfw3.h>

#include <guiproxy\gui.h>

using namespace synonms::gfx::gui;
using namespace synonms::gfx::mathematics::linear;

bool GuiHelper::show_demo_window = true;
bool GuiHelper::show_another_window = false;
float GuiHelper::clear_color[] = { 0.45f, 0.55f, 0.60f, 1.00f };

void GuiHelper::ApplyDarkStyle()
{
    proxies::imgui::Gui::ApplyDarkStyle();
}

bool GuiHelper::CollapsingHeader(const std::string& header)
{
    return proxies::imgui::Gui::CollapsingHeader(header);
}

bool GuiHelper::ColourEdit3(const std::string& label, float* values)
{
    return proxies::imgui::Gui::ColourEdit3(label, values);
}

void GuiHelper::DrawSampleWindow()
{
    {
        //static int counter = 0;

        proxies::imgui::Gui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        //proxies::imgui::Gui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        //proxies::imgui::Gui::Checkbox("Demo Window", show_demo_window);      // Edit bools storing our window open/close state
        //proxies::imgui::Gui::Checkbox("Another Window", show_another_window);

        static float f = 0.0f;
        proxies::imgui::Gui::SliderFloat("float", f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

        //proxies::imgui::Gui::ColourEdit3("clear color", clear_color); // Edit 3 floats representing a color

        //if (proxies::imgui::Gui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        //    counter++;
        //proxies::imgui::Gui::SameLine();
        //proxies::imgui::Gui::Text("counter = " + std::to_string(counter));

        auto framerate = proxies::imgui::Gui::GetFramerate();
        proxies::imgui::Gui::Text("Application average " + std::to_string(1000.0f / framerate) + " ms/frame (" + std::to_string(framerate) + " FPS)");
        proxies::imgui::Gui::End();
    }

}

Vector2<float> GuiHelper::GetDisplaySize()
{
    auto displaySize = proxies::imgui::Gui::GetDisplaySize();

    return { std::get<0>(displaySize), std::get<1>(displaySize) };
}

Vector2<float> GuiHelper::GetDisplayFramebufferScale()
{
    auto displayFramebufferScale = proxies::imgui::Gui::GetDisplayFramebufferScale();

    return { std::get<0>(displayFramebufferScale), std::get<1>(displayFramebufferScale) };
}

void* GuiHelper::Initialise(void* window, const std::string& glslVersion)
{
    return proxies::imgui::Gui::Initialise(window, glslVersion);
}

void GuiHelper::NewFrame()
{
    proxies::imgui::Gui::NewFrame();
}

void GuiHelper::PopItemWidth()
{
    proxies::imgui::Gui::PopItemWidth();
}

void GuiHelper::PopWindow()
{
    proxies::imgui::Gui::End();
}

void GuiHelper::PushItemWidth(float width)
{
    proxies::imgui::Gui::PushItemWidth(width);
}

void GuiHelper::PushWindow(const std::string& title, float x, float y, float width, float height)
{
    proxies::imgui::Gui::SetNextWindowPosition(x, y);
    proxies::imgui::Gui::SetNextWindowSize(width, height);
    proxies::imgui::Gui::Begin(title);
}

void GuiHelper::Render()
{
    proxies::imgui::Gui::Render();
}

void GuiHelper::Shutdown()
{
    proxies::imgui::Gui::Shutdown();
}

void GuiHelper::SliderFloat3(const std::string& label, float* values, float min, float max)
{
    proxies::imgui::Gui::SliderFloat3(label, values, min, max);
}

void GuiHelper::Text(const std::string& text)
{
    proxies::imgui::Gui::Text(text);
}
