#include "gui-helper.h"

#include <GLFW\glfw3.h>

#include <guiproxy\gui.h>

using namespace synonms::gfx::gui;

bool GuiHelper::show_demo_window = true;
bool GuiHelper::show_another_window = false;
float GuiHelper::clear_color[] = { 0.45f, 0.55f, 0.60f, 1.00f };

void GuiHelper::ApplyDarkStyle()
{
    proxies::imgui::Gui::ApplyDarkStyle();
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

void* GuiHelper::Initialise(void* window, const std::string& glslVersion)
{
    return proxies::imgui::Gui::Initialise(window, glslVersion);
}

void GuiHelper::NewFrame()
{
    proxies::imgui::Gui::NewFrame();
}

void GuiHelper::PopWindow()
{
    proxies::imgui::Gui::End();
}

void GuiHelper::PushWindow(const std::string& title)
{
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
