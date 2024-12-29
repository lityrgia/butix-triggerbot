#include "imgui/imgui.h"
#include "../Main/options.h"
#include <string>
#include <Windows.h>
#include "../Main/Modules/Butix.h"
#include "../SDK/Utils/xorstr.hpp"

void setImguiStyle() {
    auto& colors = ImGui::GetStyle().Colors;

    colors[ImGuiCol_ResizeGrip] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_ResizeGripActive] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_ResizeGripHovered] = ImColor(0, 0, 0, 0);

    colors[ImGuiCol_Button] = ImColor(0, 0, 0, 0);
    colors[ImGuiCol_ButtonActive] = ImColor(255, 122, 0, 255);
    colors[ImGuiCol_ButtonHovered] = ImColor(255, 140, 0, 255);

    colors[ImGuiCol_SliderGrab] = ImColor(16, 24, 32, 255);
    colors[ImGuiCol_SliderGrabActive] = ImColor(16, 24, 32, 255);

    colors[ImGuiCol_CheckMark] = ImColor(0, 0, 0, 255);

    colors[ImGuiCol_FrameBg] = ImColor(255, 255, 255);
    colors[ImGuiCol_FrameBgActive] = ImColor(255, 255, 255);
    colors[ImGuiCol_FrameBgHovered] = ImColor(255, 255, 255);

    colors[ImGuiCol_PopupBg] = ImColor(255, 255, 255, 255);

    colors[ImGuiCol_WindowBg] = ImColor(16, 24, 32, 255);

    colors[ImGuiCol_TitleBg] = ImColor(16, 24, 32, 255);
    colors[ImGuiCol_TitleBgActive] = ImColor(16, 24, 32, 255);
    colors[ImGuiCol_TitleBgCollapsed] = ImColor(16, 24, 32, 255);

    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowBorderSize = 0.0f;
    style.ChildBorderSize = 0.0f;
    style.FramePadding = ImVec2(0, 0);
    style.WindowPadding = ImVec2(0, 0);
    style.ItemSpacing = ImVec2(0, 0);
    style.WindowRounding = 5.f;
    style.FrameRounding = 4.0f;
    style.GrabMinSize = 9.f;
    style.GrabRounding = 100.f;
}


bool toggleButton(const char* str_id, bool* v, float button_width = 0.0f, float button_height = 0.0f) {
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    if (button_width == 0.0f) {
        button_width = ImGui::GetFrameHeight() * 1.55f;
    }
    if (button_height == 0.0f) {
        button_height = ImGui::GetFrameHeight();
    }

    float radius = button_height * 0.50f;

    ImGui::InvisibleButton(str_id, ImVec2(button_width, button_height));
    if (ImGui::IsItemClicked())
        *v = !*v;

    ImU32 col_bg = *v ? IM_COL32(255, 140, 0, 255) : IM_COL32(255, 255, 255, 255);
    ImU32 circle_bg = *v ? IM_COL32(255, 255, 255, 255) : IM_COL32(16, 24, 32, 255);

    draw_list->AddRectFilled(p, ImVec2(p.x + button_width, p.y + button_height), col_bg, button_height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(*v ? (p.x + button_width - radius) : (p.x + radius), p.y + radius), radius - 1.5f, circle_bg);

    return *v;
}

ImVec2 menuSize(360, 415);
ImVec2 buttonSize(40, 20);
ImVec2 paddings(0.f, 16.f);
float leftMargin = 15.f;

bool waitingForTriggerbotKey = false;
bool waitingForMenuKey = false;

bool keyPressed = false;

void renderGui()
{
    ImGui::Begin(xorstr_("Butix Triggerbot"));
    ImGui::SetWindowSize(menuSize, ImGuiCond_Always);

    ImGui::Indent(10.f);

    ImGui::Dummy(paddings);

    toggleButton(xorstr_("#triggerbotEnable"), &options::triggerbot::isEnabled, buttonSize.x, buttonSize.y);
    ImGui::SameLine();
    ImGui::Text(xorstr_(" Enabled"));

    ImGui::Dummy(paddings);

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(16.f / 255.f, 24.f / 255.f, 32.f / 255.f, 1.f));
    ImGui::SliderInt("0", &options::triggerbot::delay, 5, 1500, "%d");
    ImGui::PopStyleColor();
    ImGui::SameLine();
    ImGui::Text(xorstr_(" Delay"));

    ImGui::Dummy(paddings);

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(16.f / 255.f, 24.f / 255.f, 32.f / 255.f, 1.f));
    ImGui::SliderFloat("1", &options::triggerbot::hitChance, 5, 100, "%.2f");
    ImGui::PopStyleColor();
    ImGui::SameLine();
    ImGui::Text(xorstr_(" Hit chance"));
    
    ImGui::Dummy(paddings);
    
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(16.f / 255.f, 24.f / 255.f, 32.f / 255.f, 1.f));
    ImGui::SliderInt("2", &options::triggerbot::randomFactorMs, 0, 200, "%d");
    ImGui::PopStyleColor();
    ImGui::SameLine();
    ImGui::Text(xorstr_(" Random Fact"));
    
    ImGui::Dummy(paddings);
    
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(16.f / 255.f, 24.f / 255.f, 32.f / 255.f, 1.f));
    ImGui::SliderFloat("3", &options::triggerbot::distance, 0, 4, "%.2f");
    ImGui::PopStyleColor();
    ImGui::SameLine();
    ImGui::Text(xorstr_(" Distance"));
    
    ImGui::Dummy(paddings);

    toggleButton("#am", &options::triggerbot::attackMobs, buttonSize.x, buttonSize.y);
    ImGui::SameLine();
    ImGui::Text(xorstr_(" Mobs"));

    ImGui::SameLine();
    ImGui::Dummy(ImVec2{ 81, 0 });
    ImGui::SameLine();

    toggleButton("#ab", &options::triggerbot::attackPlayers, buttonSize.x, buttonSize.y);
    ImGui::SameLine();
    ImGui::Text(xorstr_(" Players"));

    ImGui::Dummy(paddings);

    toggleButton("#ai", &options::triggerbot::attackInvisibles, buttonSize.x, buttonSize.y);
    ImGui::SameLine();
    ImGui::Text(xorstr_(" Invisibles"));

    ImGui::SameLine();
    ImGui::Dummy(ImVec2{ 50, 0 });
    ImGui::SameLine();

    toggleButton("#oc", &options::triggerbot::onlyCrits, buttonSize.x, buttonSize.y);
    ImGui::SameLine();
    ImGui::Text(xorstr_(" Only crits"));

    ImGui::Dummy(paddings);
    
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.f, 140.f / 255, 0, 1.f));

    if (ImGui::Button(xorstr_(" Triggerbot key"), ImVec2(130, 25))) {
        waitingForTriggerbotKey = true;
    }

    ImGui::SameLine();
    ImGui::Dummy(ImVec2{ 40, 0 });
    ImGui::SameLine();

    if (ImGui::Button(xorstr_(" Menu key"), ImVec2(130, 25))) {
        waitingForMenuKey = true;
    }

    ImGui::Dummy(paddings);

    if (waitingForTriggerbotKey) {
        ImGui::Text(xorstr_("Press key..."));

        for (int key = 0; key < 256; ++key) {
            if (GetAsyncKeyState(key) & 0x8000) {
                options::triggerbot::toggleButton = key;
                waitingForTriggerbotKey = false;
                break;
            }
        }
    }
    else {
        ImGui::Text(xorstr_("Key: % s"), ImGui::GetKeyName(static_cast<ImGuiKey>(options::triggerbot::toggleButton)));
    }
    
    ImGui::SameLine();
    ImGui::Dummy(ImVec2{ 103, 0 });
    ImGui::SameLine();

    if (waitingForMenuKey) {
        ImGui::Text(xorstr_("Press key..."));

        for (int key = 0; key < 256; ++key) {
            if (GetAsyncKeyState(key) & 0x8000) {
                options::menu::toggleButton = key;
                waitingForMenuKey = false;
                break;
            }
        }
    }
    else {
        ImGui::Text(xorstr_("Key: % s"), ImGui::GetKeyName(static_cast<ImGuiKey>(options::menu::toggleButton)));
    }

    ImGui::Dummy(paddings);

    if (ImGui::Button(xorstr_("Detach"), ImVec2{ 80, 30 })) {
        butix::instance->shouldDetach();
    }

    ImGui::PopStyleColor();
    ImGui::End();
}