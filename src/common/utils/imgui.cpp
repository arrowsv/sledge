#include "imgui.hpp"
#include "common/utils/os.hpp"
#include "fonts.hpp"

#include <imgui.h>
#include <magic_enum.hpp>

namespace utils::imgui {
void initialize_styles() {

    /// MIT License
    /// Copyright (c) 2026 Logersnamed (https://github.com/Logersnamed/FreecamMod)
    /// Modified by arrowsv

    ImGuiStyle& style = ImGui::GetStyle();

    // Layout
    style.WindowPadding = ImVec2(12, 12);
    style.FramePadding = ImVec2(8, 4);
    style.ItemSpacing = ImVec2(8, 6);
    style.ItemInnerSpacing = ImVec2(6, 4);
    style.IndentSpacing = 14.0f;
    style.ScrollbarSize = 11.0f;
    style.GrabMinSize = 10.0f;
    style.CellPadding = ImVec2(6, 4);

    // Rounding
    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.ChildRounding = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding = 4.0f;
    style.TabRounding = 4.0f;

    // Borders
    style.WindowBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.TabBorderSize = 0.0f;
    style.SeparatorTextBorderSize = 1.0f;

    // Palette
    const ImVec4 bg1 = ImVec4(0.06f, 0.06f, 0.07f, 1.00f);
    const ImVec4 bg2 = ImVec4(0.09f, 0.09f, 0.10f, 1.00f);
    const ImVec4 bg3 = ImVec4(0.11f, 0.11f, 0.13f, 1.00f);
    const ImVec4 bg4 = ImVec4(0.14f, 0.14f, 0.17f, 1.00f);
    const ImVec4 bg5 = ImVec4(0.17f, 0.17f, 0.20f, 1.00f);
    const ImVec4 bg6 = ImVec4(0.15f, 0.15f, 0.17f, 1.00f);
    const ImVec4 bg7 = ImVec4(0.18f, 0.18f, 0.21f, 1.00f);
    const ImVec4 bg8 = ImVec4(0.20f, 0.20f, 0.24f, 1.00f);
    const ImVec4 bg9 = ImVec4(0.25f, 0.25f, 0.30f, 1.00f);

    const ImVec4 ui0 = ImVec4(0.22f, 0.22f, 0.25f, 1.00f);
    const ImVec4 ui1 = ImVec4(0.44f, 0.44f, 0.47f, 1.00f);
    const ImVec4 ui2 = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    const ImVec4 ui3 = ImVec4(0.40f, 0.40f, 0.45f, 1.00f);

    const ImVec4 text = ImVec4(0.88f, 0.88f, 0.90f, 1.00f);

    const ImVec4 acc0 = ImVec4(0.29f, 0.50f, 0.83f, 1.00f);
    const ImVec4 acc1 = ImVec4(0.38f, 0.62f, 0.90f, 1.00f);
    const ImVec4 acc2 = ImVec4(0.19f, 0.38f, 0.69f, 1.00f);

    auto with_alpha = [](ImVec4 v, float a) {
        v.w = a;
        return v;
    };

    ImVec4* colors = style.Colors;

    // Text
    colors[ImGuiCol_Text] = text;
    colors[ImGuiCol_TextDisabled] = ui1;

    // Backgrounds
    colors[ImGuiCol_WindowBg] = bg1;
    colors[ImGuiCol_ChildBg] = bg2;
    colors[ImGuiCol_PopupBg] = bg2;

    // Borders
    colors[ImGuiCol_Border] = ui0;
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // Frames
    colors[ImGuiCol_FrameBg] = bg3;
    colors[ImGuiCol_FrameBgHovered] = bg6;
    colors[ImGuiCol_FrameBgActive] = bg7;

    // Title
    colors[ImGuiCol_TitleBg] = bg1;
    colors[ImGuiCol_TitleBgActive] = bg2;
    colors[ImGuiCol_TitleBgCollapsed] = with_alpha(bg1, 0.75f);

    // Scrollbar
    colors[ImGuiCol_ScrollbarBg] = bg1;
    colors[ImGuiCol_ScrollbarGrab] = ui0;
    colors[ImGuiCol_ScrollbarGrabHovered] = ui2;
    colors[ImGuiCol_ScrollbarGrabActive] = ui3;

    // Accent
    colors[ImGuiCol_CheckMark] = acc1;
    colors[ImGuiCol_SliderGrab] = acc0;
    colors[ImGuiCol_SliderGrabActive] = acc2;

    // Buttons
    colors[ImGuiCol_Button] = bg5;
    colors[ImGuiCol_ButtonHovered] = acc0;
    colors[ImGuiCol_ButtonActive] = acc2;

    // Headers
    colors[ImGuiCol_Header] = bg4;
    colors[ImGuiCol_HeaderHovered] = bg8;
    colors[ImGuiCol_HeaderActive] = bg9;

    // Separator
    colors[ImGuiCol_Separator] = ui0;
    colors[ImGuiCol_SeparatorHovered] = with_alpha(acc0, 0.78f);
    colors[ImGuiCol_SeparatorActive] = acc0;

    // Resize grip
    colors[ImGuiCol_ResizeGrip] = with_alpha(acc0, 0.15f);
    colors[ImGuiCol_ResizeGripHovered] = with_alpha(acc0, 0.50f);
    colors[ImGuiCol_ResizeGripActive] = with_alpha(acc0, 0.90f);

    // Tabs
    colors[ImGuiCol_Tab] = bg2;
    colors[ImGuiCol_TabHovered] = bg8;
    colors[ImGuiCol_TabSelected] = bg4;
    colors[ImGuiCol_TabSelectedOverline] = acc0;
    colors[ImGuiCol_TabDimmed] = ImVec4(0.07f, 0.07f, 0.08f, 1.00f);
    colors[ImGuiCol_TabDimmedSelected] = bg3;
    colors[ImGuiCol_TabDimmedSelectedOverline] = with_alpha(acc0, 0.40f);

    // Misc
    colors[ImGuiCol_NavHighlight] = acc0;
    colors[ImGuiCol_NavWindowingHighlight] = with_alpha(acc0, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg] = with_alpha(bg1, 0.50f);
    colors[ImGuiCol_ModalWindowDimBg] = with_alpha(bg1, 0.60f);

    // ImGuiStyle *style = &ImGui::GetStyle();
    // style->WindowPadding = ImVec2(8, 8);
    // style->FramePadding = ImVec2(8, 4);
    // style->ItemSpacing = ImVec2(8, 4);
    // style->ItemInnerSpacing = ImVec2(8, 4);
    // style->ScrollbarPadding = 4;

    // style->WindowTitleAlign = ImVec2(0.50, 0.50);
    // style->SeparatorSize = 1;
    // style->SeparatorTextBorderSize = 1;
    // style->WindowBorderSize = 1;
    // style->ChildBorderSize = 1;
    // style->PopupBorderSize = 1;
    // style->FrameBorderSize = 0;
    // style->GrabMinSize = 12;

    // style->ItemSpacing = ImVec2(8.0f, 4.0f);
    // style->ItemInnerSpacing = ImVec2(8.0f, 4.0f);
    // style->ScrollbarSize = 14.0f;
    // style->IndentSpacing = 14.0f;

    // style->ChildRounding = 4;
    // style->FrameRounding = 4;
    // style->GrabRounding = 4;
    // style->PopupRounding = 4;
    // style->ScrollbarRounding = 4;
    // style->TabRounding = 4;
    // style->WindowRounding = 4;

    // ImVec4 *colors = style->Colors;
    // colors[ImGuiCol_Text] = ImVec4(0.93f, 0.93f, 0.93f, 1.00f);
    // colors[ImGuiCol_TextDisabled] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
    // colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
    // colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    // colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.07f, 0.98f);
    // colors[ImGuiCol_Border] = ImVec4(0.95f, 0.90f, 0.99f, 0.19f);
    // colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    // colors[ImGuiCol_FrameBg] = ImVec4(0.38f, 0.31f, 0.26f, 0.27f);
    // colors[ImGuiCol_FrameBgHovered] = ImVec4(0.48f, 0.35f, 0.26f, 0.53f);
    // colors[ImGuiCol_FrameBgActive] = ImVec4(0.48f, 0.35f, 0.26f, 0.86f);
    // colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    // colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    // colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    // colors[ImGuiCol_MenuBarBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
    // colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    // colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    // colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    // colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    // colors[ImGuiCol_CheckMark] = ImVec4(0.93f, 0.93f, 0.93f, 1.00f);
    // colors[ImGuiCol_CheckboxSelectedBg] = ImVec4(0.48f, 0.35f, 0.26f, 0.86f);
    // colors[ImGuiCol_SliderGrab] = ImVec4(0.48f, 0.35f, 0.26f, 0.78f);
    // colors[ImGuiCol_SliderGrabActive] = ImVec4(0.48f, 0.35f, 0.26f, 1.00f);
    // colors[ImGuiCol_Button] = ImVec4(0.48f, 0.35f, 0.26f, 0.78f);
    // colors[ImGuiCol_ButtonHovered] = ImVec4(0.48f, 0.35f, 0.26f, 0.92f);
    // colors[ImGuiCol_ButtonActive] = ImVec4(0.48f, 0.35f, 0.26f, 1.00f);
    // colors[ImGuiCol_Header] = ImVec4(0.48f, 0.35f, 0.26f, 0.78f);
    // colors[ImGuiCol_HeaderHovered] = ImVec4(0.48f, 0.35f, 0.26f, 0.92f);
    // colors[ImGuiCol_HeaderActive] = ImVec4(0.48f, 0.35f, 0.26f, 1.00f);
    // colors[ImGuiCol_Separator] = ImVec4(0.95f, 0.90f, 0.99f, 0.19f);
    // colors[ImGuiCol_SeparatorHovered] = ImVec4(0.93f, 0.91f, 1.00f, 0.25f);
    // colors[ImGuiCol_SeparatorActive] = ImVec4(0.93f, 0.91f, 1.00f, 0.36f);
    // colors[ImGuiCol_ResizeGrip] = ImVec4(0.48f, 0.35f, 0.26f, 0.78f);
    // colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.48f, 0.35f, 0.26f, 0.92f);
    // colors[ImGuiCol_ResizeGripActive] = ImVec4(0.48f, 0.35f, 0.26f, 1.00f);
    // colors[ImGuiCol_InputTextCursor] = ImVec4(0.93f, 0.93f, 0.93f, 1.00f);
    // colors[ImGuiCol_TabHovered] = ImVec4(0.48f, 0.35f, 0.26f, 0.92f);
    // colors[ImGuiCol_Tab] = ImVec4(0.48f, 0.35f, 0.26f, 0.78f);
    // colors[ImGuiCol_TabSelected] = ImVec4(0.48f, 0.35f, 0.26f, 1.00f);
    // colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.48f, 0.35f, 0.26f, 1.00f);
    // colors[ImGuiCol_TabDimmed] = ImVec4(0.48f, 0.35f, 0.26f, 0.78f);
    // colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.48f, 0.35f, 0.26f, 1.00f);
    // colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
    // colors[ImGuiCol_DockingPreview] = ImVec4(0.48f, 0.35f, 0.26f, 1.00f);
    // colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    // colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    // colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    // colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    // colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    // colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    // colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    // colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    // colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    // colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    // colors[ImGuiCol_TextLink] = ImVec4(0.67f, 0.50f, 0.37f, 1.00f);
    // colors[ImGuiCol_TextSelectedBg] = ImVec4(0.48f, 0.35f, 0.26f, 0.78f);
    // colors[ImGuiCol_TreeLines] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    // colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    // colors[ImGuiCol_DragDropTargetBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    // colors[ImGuiCol_UnsavedMarker] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    // colors[ImGuiCol_NavCursor] = ImVec4(0.67f, 0.50f, 0.37f, 1.00f);
    // colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    // colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    // colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

void initialize_fonts() {
    ImGuiIO& io = ImGui::GetIO();

    ImFontConfig font_cfg;
    font_cfg.FontDataOwnedByAtlas = false;

    float size_pixels = 14.0f;
    ImFont* roboto_medium =
        io.Fonts->AddFontFromMemoryTTF((void*)fonts::roboto_regular_ttf.data(),
                                       fonts::roboto_regular_ttf.size(), size_pixels, &font_cfg);
    io.FontDefault = roboto_medium;
}

bool key_combobox(const char* label, os::key* current_key) {
    constexpr auto entries = magic_enum::enum_entries<os::key>();
    std::string current_name = std::string(magic_enum::enum_name(*current_key));

    if (current_name.empty()) {
        *current_key = os::key::none;
        current_name = magic_enum::enum_name(os::key::none);
    }

    bool value_changed = false;
    if (ImGui::BeginCombo(label, current_name.c_str())) {
        for (const auto& [code, name] : entries) {
            const bool is_selected = (*current_key == code);

            if (ImGui::Selectable(name.data(), is_selected)) {
                *current_key = code;
                value_changed = true;
            }

            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    return value_changed;
}

void set_help_marker(const std::string& text) {
    if (begin_help_marker()) {
        ImGui::Text("%s", text.c_str());
        end_help_marker();
    }
}
bool begin_help_marker() {
    ImGui::SameLine();
    ImGui::TextDisabled("(?)");
    return ImGui::BeginItemTooltip();
}
void end_help_marker() { ImGui::EndTooltip(); }
} // namespace utils::imgui
