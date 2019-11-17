#include "gui.h"

#include <GL\glew.h>

#include <vendor\imgui\imgui.h>
#include <vendor\imgui\imgui_impl_glfw.h>
#include <vendor\imgui\imgui_impl_opengl3.h>

using namespace synonms::gfx::proxies::imgui;

void Gui::ApplyDarkStyle()
{
    ImGui::StyleColorsDark();
}

bool Gui::Begin(const std::string& name)
{
    return ImGui::Begin(name.c_str());
}

bool Gui::Button(const std::string& label)
{
    return ImGui::Button(label.c_str());
}

bool Gui::Checkbox(const std::string& label, bool& showAnotherWindow)
{
    return ImGui::Checkbox(label.c_str(), &showAnotherWindow);
}

bool Gui::CollapsingHeader(const std::string& header)
{
    return ImGui::CollapsingHeader(header.c_str());
}

bool Gui::ColourEdit3(const std::string& label, float* colorValues)
{
    return ImGui::ColorEdit3(label.c_str(), colorValues);
}

void Gui::End()
{
    ImGui::End();
}

std::tuple<float, float> Gui::GetDisplayFramebufferScale()
{
    auto& io = ImGui::GetIO();    

    return std::make_tuple(io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
}

std::tuple<float, float> Gui::GetDisplaySize()
{
    auto& io = ImGui::GetIO();

    return std::make_tuple(io.DisplaySize.x, io.DisplaySize.y);
}

float Gui::GetFramerate()
{
    return ImGui::GetIO().Framerate;
}

void* Gui::Initialise(void* window, const std::string& glslVersion)
{
    auto context = ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)window, true);
    ImGui_ImplOpenGL3_Init(glslVersion.c_str());

    return context;
}

void Gui::NewFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::PopItemWidth()
{
    ImGui::PopItemWidth();
}

void Gui::PushItemWidth(float width)
{
    ImGui::PushItemWidth(width);
}

void Gui::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::SameLine()
{
    ImGui::SameLine();
}

void Gui::SetNextWindowPosition(float x, float y)
{
    ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_FirstUseEver);
}

void Gui::SetNextWindowSize(float width, float height)
{
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);
}

void Gui::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

bool Gui::SliderFloat(const std::string& label, float& value, float min, float max)
{
    return ImGui::SliderFloat(label.c_str(), &value, min, max);
}

bool Gui::SliderFloat3(const std::string& label, float* values, float min, float max)
{
    return ImGui::SliderFloat3(label.c_str(), values, min, max);
}

void Gui::Text(const std::string& text)
{
    ImGui::Text(text.c_str());
}
