#include "imgui.hpp"
#include "common/assets/fonts/icons.hpp"
#include "common/utils/os.hpp"

#include <imgui.h>
#include <magic_enum.hpp>

namespace {
    unsigned char base_font_data[] = {
#include "roboto_medium.ttf.h"
    };

    unsigned char icon_font_data[] = {
#include "material_icons_round.ttf.h"
    };
}

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
    }

    void initialize_fonts() {
        ImGuiIO& io = ImGui::GetIO();

        float size_pixels = 14.0f;

        // Base font
        ImFontConfig base_config;
        base_config.FontDataOwnedByAtlas = false;
        base_config.OversampleH = 3;
        base_config.OversampleV = 3;
        ImFont* roboto_medium = io.Fonts->AddFontFromMemoryTTF(
            base_font_data, sizeof(base_font_data), size_pixels, &base_config);
        io.FontDefault = roboto_medium;

        // Icon font
        ImFontConfig icon_config;
        icon_config.FontDataOwnedByAtlas = false;
        icon_config.MergeMode = true;
        icon_config.PixelSnapH = true;
        icon_config.GlyphMinAdvanceX = size_pixels;
        icon_config.GlyphMaxAdvanceX = size_pixels;
        icon_config.GlyphOffset.y = 2.0f;

        static const ImWchar icon_ranges[] = {ICON_MIN_MD, ICON_MAX_MD, 0};
        io.Fonts->AddFontFromMemoryTTF(icon_font_data, sizeof(icon_font_data), size_pixels,
                                       &icon_config, icon_ranges);
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
        ImGui::TextDisabled(ICON_MS_QUESTION_MARK);
        return ImGui::BeginItemTooltip();
    }
    void end_help_marker() { ImGui::EndTooltip(); }
}
