#include "mods.hpp"

#include "common/config.hpp"
#include "common/mods.hpp"
#include "common/utils/imgui.hpp"

#include <imgui.h>
#include <imgui_stdlib.h>

namespace {
    config temp_config;
    std::string selected_mod_id = "";
}

namespace gui {
    void draw_mods_modal() {
        ImVec2 main_window_size = ImGui::GetMainViewport()->Size;
        float padding = ImGui::GetStyle().WindowPadding.x;
        ImVec2 mods_modal_size = {main_window_size.x - (padding * 2.0f),
                                  main_window_size.y - (padding * 2.0f)};
        ImGui::SetNextWindowSize(mods_modal_size, ImGuiCond_Always);
        if (ImGui::BeginPopupModal("Mods", NULL,
                                   ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
            if (ImGui::IsWindowAppearing()) {
                temp_config = config::get();
            }

            float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;
            float bottom_section_height = item_spacing_y + item_spacing_y + ImGui::GetFrameHeight();
            float child_height = ImGui::GetContentRegionAvail().y - bottom_section_height;
            float mod_list_width = ImGui::GetContentRegionAvail().x * 0.40;

            auto discovered_mods = mods::manager::get().get_discovered_mods();

            if (ImGui::BeginChild("mod_list", {mod_list_width, child_height},
                                  ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX,
                                  ImGuiWindowFlags_HorizontalScrollbar)) {
                for (const auto& mod : discovered_mods) {
                    auto state = temp_config.sledge.mod_states.find(mod.id);
                    if (state == temp_config.sledge.mod_states.end())
                        continue;

                    ImGui::PushID(mod.id.c_str());

                    ImGui::Checkbox("##enabled", &state->second.enabled);
                    ImGui::SameLine();
                    if (ImGui::Selectable(mod.name.c_str(), selected_mod_id == mod.id)) {
                        selected_mod_id = mod.id;
                    }

                    ImGui::PopID();
                }
            }
            ImGui::EndChild();
            ImGui::SameLine();

            if (ImGui::BeginChild("mod_info", {ImGui::GetContentRegionAvail().x, child_height},
                                  ImGuiChildFlags_Borders)) {
                auto mod_it = std::ranges::find_if(
                    discovered_mods, [](const auto& m) { return m.id == selected_mod_id; });

                if (mod_it != discovered_mods.end()) {
                    const mods::mod_info& mod = *mod_it;

                    // ImGui::TextUnformatted(mod.name.c_str());

                    // ImGui::Separator();
                    // ImGui::Spacing();

                    if (utils::imgui::begin_property_table("mod_info")) {
                        utils::imgui::begin_property_row("ID");
                        ImGui::TextUnformatted(mod.id.c_str());
                        utils::imgui::end_property_row();

                        utils::imgui::begin_property_row("Name");
                        ImGui::TextUnformatted(mod.name.c_str());
                        utils::imgui::end_property_row();

                        utils::imgui::begin_property_row("Authors");
                        std::string author_str = "";

                        bool is_first = true;
                        for (const auto& author : mod.authors) {
                            if (!is_first) {
                                author_str += ", ";
                            }
                            author_str += author;
                            is_first = false;
                        }
                        
                        ImGui::TextUnformatted(author_str.c_str());
                        utils::imgui::end_property_row();

                        utils::imgui::begin_property_row("Version");
                        ImGui::TextUnformatted(mod.version.c_str());
                        utils::imgui::end_property_row();

                        utils::imgui::end_property_table();
                    }

                    if (!mod.description.empty()) {
                        ImGui::SeparatorText("Description");
                        ImGui::TextWrapped("%s", mod.description.c_str());
                    }

                    if (!mod.options.empty()) {
                        ImGui::SeparatorText("Options");
                        auto& current_mod_state = temp_config.sledge.mod_states[mod.id];

                        auto& options_map = current_mod_state.options;

                        std::string table_id = mod.id + "_options";
                        if (utils::imgui::begin_property_table(table_id.c_str())) {

                            for (const mods::mod_option& option : mod.options) {
                                std::string& current_selection = options_map[option.name];

                                std::string id = std::format("##{}", option.name);
                                bool has_tooltip = !option.tooltip.empty();

                                utils::imgui::begin_property_row(option.name.c_str());
                                switch (option.type) {
                                    case mods::mod_option_type::custom: {
                                        ImGui::InputText(id.c_str(), &current_selection);
                                        break;
                                    }
                                    case mods::mod_option_type::key: {
                                        utils::os::key current_key =
                                            utils::os::key_from_string(current_selection);

                                        if (utils::imgui::key_combobox(id.c_str(), &current_key)) {
                                            current_selection =
                                                utils::os::key_to_string(current_key);
                                        }
                                        break;
                                    }
                                    case mods::mod_option_type::checkbox: {
                                        bool is_checked = (current_selection == "true");
                                        if (ImGui::Checkbox(id.c_str(), &is_checked)) {
                                            current_selection = is_checked ? "true" : "false";
                                        }
                                        break;
                                    }
                                    case mods::mod_option_type::multiple: {
                                        if (ImGui::BeginCombo(id.c_str(),
                                                              current_selection.c_str())) {
                                            for (const std::string& val : option.choice_multiple) {
                                                bool is_selected = (current_selection == val);

                                                if (ImGui::Selectable(val.c_str(), is_selected)) {
                                                    current_selection = val;
                                                }
                                                if (is_selected) {
                                                    ImGui::SetItemDefaultFocus();
                                                }
                                            }
                                            ImGui::EndCombo();
                                        }
                                        break;
                                    }
                                }
                                utils::imgui::end_property_row();

                                if (has_tooltip || !option.choice_default.empty()) {
                                    if (utils::imgui::begin_tooltip()) {
                                        if (has_tooltip) {
                                            ImGui::TextUnformatted(option.tooltip.c_str());
                                        }

                                        if (!option.choice_default.empty()) {
                                            if (utils::imgui::begin_property_table("default")) {
                                                utils::imgui::begin_property_row("Default");
                                                ImGui::TextUnformatted(
                                                    option.choice_default.c_str());
                                                utils::imgui::end_property_row();
                                                utils::imgui::end_property_table();
                                            }
                                        }

                                        utils::imgui::end_tooltip();
                                    }
                                }
                            }
                            utils::imgui::end_property_table();
                        }
                    }
                } else {
                    ImGui::TextDisabled("No mod selected.");
                }
            }
            ImGui::EndChild();

            int button_count = 3;
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
            if (ImGui::Button("Rescan", {button_width, 0})) {
                auto sledge_dir = utils::os::get_module_directory(nullptr);

                config::get().initialize(sledge_dir);
                mods::manager::get().initialize(sledge_dir / "mods");
                selected_mod_id = "";
                temp_config = config::get();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", {button_width, 0})) {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
}