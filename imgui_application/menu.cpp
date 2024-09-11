#include "ImGui/ImGui.h"
#include "ImGui/imgui_impl_dx9.h"
#include "ImGui/imgui_impl_win32.h"

#include "menu.h"
#include "color.h"

#include <iostream>
#include <string>
#include <windows.h>

extern bool menu::active = true;
extern bool menu::debug_console = true;
extern std::vector<std::string> menu::saved_rgb = { };

class initWindow
{
public:
    const char* window_title = "QuickColor";
    ImVec2 window_size = { 200, 70 };
    bool styles_loaded = false;

    DWORD window_flags = ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize;
} iw;

void load_styles()
{
    iw.styles_loaded = true;

    ImVec4* colors = ImGui::GetStyle().Colors;
    {
        colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
        colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.30f, 0.50f);

        colors[ImGuiCol_FrameBg] = ImVec4(0.41f, 0.55f, 0.38f, 1.00f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.61f, 0.72f, 0.58f, 1.00f);

        colors[ImGuiCol_TitleBg] = ImVec4(0.41f, 0.55f, 0.38f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.41f, 0.55f, 0.38f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.41f, 0.55f, 0.38f, 1.00f);

        colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.00f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 0.00f);
    }

    ImGuiStyle* style = &ImGui::GetStyle();
    {
        style->FrameRounding = 3.f;
    }
}


void menu::render()
{
    ImVec4 col = ImColor(color::r, color::g, color::b);
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    if (!iw.styles_loaded)
        load_styles();

    if (menu::active)
    {
        ImGui::SetNextWindowBgAlpha(1.0f);
        ImGui::Begin(iw.window_title, &menu::active, iw.window_flags);
        {
            ImGui::Text("Right click to copy the hovered colors RGB value.");
            ImGui::ColorEdit4("##picker", (float*)&col);

            ImGui::Separator();
            
            ImGui::Text("Colors grabbed this session:");
            if (menu::saved_rgb.size() == 0)
                ImGui::TextDisabled("No colors have been grabbed this session.");
            for (int count = 0; count < menu::saved_rgb.size(); count++)
            {
                ImGui::TextDisabled("[%d]", (count + 1));
                ImGui::SameLine();
                ImGui::Text(menu::saved_rgb[count].c_str());          
            }
        }
        ImGui::End();
    }
    else
    {
        exit(0);
    }
}