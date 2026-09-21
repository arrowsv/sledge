#include "options.hpp"

#include "common/config.hpp"
#include "common/utils/imgui.hpp"

#include <imgui.h>

namespace {
    config temp_config;
    std::string selected_category = "General";

    void draw_general_options() {
        if (utils::imgui::begin_property_table("general_options")) {
            utils::imgui::begin_property_row("Overlay key");
            utils::imgui::key_combobox("##overlay_key", &temp_config.sledge.overlay_key);
            utils::imgui::end_property_row();

            utils::imgui::begin_property_row("Keep launcher open");
            ImGui::Checkbox("##keep_open", &temp_config.sledge.keep_launcher_open);
            utils::imgui::end_property_row();

            utils::imgui::begin_property_row("Skip startup videos");
            ImGui::Checkbox("##skip_videos", &temp_config.game.skip_startup_videos);
            utils::imgui::end_property_row();

            utils::imgui::end_property_table();
        }
    }

    void draw_debug_options() {
        if (utils::imgui::begin_property_table("debug_options")) {
            utils::imgui::begin_property_row("Enable debug logs");
            ImGui::Checkbox("##enable_debug_logs", &temp_config.sledge.debug_logs_enabled);
            utils::imgui::end_property_row();

            utils::imgui::begin_property_row("ImGui demo window");
            ImGui::Checkbox("##imgui_demo_window", &temp_config.sledge.imgui_demo_window);
            utils::imgui::end_property_row();

            utils::imgui::end_property_table();
        }
    }

    struct option_category {
        const char* name;
        void (*draw)();
    };

    constexpr option_category categories[] = {
        {"General", draw_general_options},
        {"Debug", draw_debug_options},
    };
}

namespace gui {
    void draw_options_modal() {
        ImVec2 main_window_size = ImGui::GetMainViewport()->Size;
        float padding = ImGui::GetStyle().WindowPadding.x;
        ImVec2 mods_modal_size = {main_window_size.x - (padding * 2.0f),
                                  main_window_size.y - (padding * 2.0f)};
        ImGui::SetNextWindowSize(mods_modal_size, ImGuiCond_Always);
        if (ImGui::BeginPopupModal("Options", NULL,
                                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
            if (ImGui::IsWindowAppearing()) {
                temp_config = config::get();
            }

            float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;
            float bottom_section_height = item_spacing_y + item_spacing_y + ImGui::GetFrameHeight();
            float child_height = ImGui::GetContentRegionAvail().y - bottom_section_height;
            float sidebar_width = ImGui::GetContentRegionAvail().x * 0.25;

            if (ImGui::BeginChild("options_sidebar", {sidebar_width, child_height},
                                  ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX, ImGuiWindowFlags_HorizontalScrollbar)) {
                for (const auto& category : categories) {
                    if (ImGui::Selectable(category.name, selected_category == category.name)) {
                        selected_category = category.name;
                    }
                }
            }
            ImGui::EndChild();
            ImGui::SameLine();
            if (ImGui::BeginChild("options_content",
                                  {ImGui::GetContentRegionAvail().x, child_height},
                                  ImGuiChildFlags_Borders, ImGuiWindowFlags_HorizontalScrollbar)) {
                for (const auto& category : categories) {
                    if (selected_category == category.name) {
                        category.draw();
                        break;
                    }
                }
            }
            ImGui::EndChild();

            int button_count = 2;
            float button_width = (ImGui::GetContentRegionAvail().x -
                                  (ImGui::GetStyle().ItemSpacing.x * (button_count - 1))) /
                                 button_count;

            ImGui::Spacing();
            if (ImGui::Button("Apply", {button_width, 0})) {
                config::get() = temp_config;
                config::get().save();
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", {button_width, 0})) {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
}