#include "mods.hpp"

#include "common/assets/fonts/icons.hpp"
#include "common/config.hpp"
#include "common/constants.hpp"
#include "common/mods.hpp"
#include "common/utils/imgui.hpp"

#include <imgui.h>
#include <imgui_stdlib.h>
#include <string>

namespace {
    config temp_config;
    std::string selected_mod_id = "";
    std::string search_text = "";

    constexpr ImVec4 warning_color = {1.0f, 0.75f, 0.2f, 1.0f};

    void open_mods_folder() {
        std::filesystem::path dir = utils::os::get_module_directory(nullptr) / "mods";

        std::error_code ec;
        std::filesystem::create_directories(dir, ec);

        ShellExecuteW(nullptr, L"open", dir.c_str(), nullptr, nullptr, SW_SHOWDEFAULT);
    }

    void rescan_mods() {
        auto sledge_dir = utils::os::get_module_directory(nullptr);

        config::get().initialize(sledge_dir);
        mods::manager::get().initialize(sledge_dir / "mods");
        selected_mod_id = "";
        temp_config = config::get();
    }

    std::string api_warning_text(const mods::mod_info& mod) {
        return std::format("This mod is written for API version {}, but this Sledge "
                           "version provides {}.\n\nUpdate Sledge to make sure it works "
                           "correctly.",
                           mod.api_version, constants::api_version.to_string());
    }

    void draw_toolbar() {
        const ImGuiStyle& style = ImGui::GetStyle();

        const char* open_label = ICON_MD_FOLDER_OPEN " Open mods folder";
        const char* rescan_label = ICON_MD_REFRESH " Rescan";
        const char* ff_label = ICON_MD_OPEN_IN_NEW " FactionFiles";

        auto button_width = [&](const char* label) {
            return ImGui::CalcTextSize(label).x + style.FramePadding.x * 2.0f;
        };

        float buttons_width = button_width(open_label) + button_width(rescan_label) +
                              button_width(ff_label) + style.ItemSpacing.x * 3.0f;

        ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - buttons_width);
        ImGui::InputTextWithHint("##mod_search", ICON_MD_SEARCH " Search mods", &search_text);

        ImGui::SameLine();
        if (ImGui::Button(open_label)) {
            open_mods_folder();
        }

        ImGui::SameLine();
        if (ImGui::Button(rescan_label)) {
            rescan_mods();
        }

        ImGui::SameLine();
        if (ImGui::Button(ff_label)) {
            ShellExecuteA(0, "open",
                          "https://www.factionfiles.com/ff.php?action=files&file_category=52", NULL,
                          NULL, SW_SHOWDEFAULT);
        }
    }

    void draw_mod_list() {
        const auto& discovered_mods = mods::manager::get().get_discovered_mods();

        if (discovered_mods.empty()) {
            ImGui::TextDisabled("No mods found.");
            return;
        }

        bool any_visible = false;
        for (const auto& mod : discovered_mods) {
            auto state = temp_config.sledge.mod_states.find(mod.id);
            if (state == temp_config.sledge.mod_states.end()) {
                continue;
            }

            if (!search_text.empty()) {
                auto it = std::ranges::search(mod.name, search_text, [](char a, char b) {
                    return std::tolower(static_cast<unsigned char>(a)) ==
                           std::tolower(static_cast<unsigned char>(b));
                });

                if (it.empty()) {
                    continue;
                }
            }
            any_visible = true;

            ImGui::PushID(mod.id.c_str());

            ImGui::Checkbox("##enabled", &state->second.enabled);
            ImGui::SameLine();

            bool dim = !state->second.enabled;
            if (dim) {
                ImGui::PushStyleColor(ImGuiCol_Text,
                                      ImGui::GetStyleColorVec4(ImGuiCol_TextDisabled));
            }

            if (ImGui::Selectable(mod.name.c_str(), selected_mod_id == mod.id)) {
                selected_mod_id = mod.id;
            }

            if (dim) {
                ImGui::PopStyleColor();
            }

            if (!mod.api_compatible) {
                ImGui::SameLine();
                ImGui::TextColored(warning_color, ICON_MD_WARNING);
                utils::imgui::set_tooltip(api_warning_text(mod));
            }

            ImGui::PopID();
        }

        if (!discovered_mods.empty() && !any_visible) {
            ImGui::TextDisabled("No mods match '%s'.", search_text.c_str());
        }
    }

    void draw_mod_option(const mods::mod_option& option,
                         std::map<std::string, std::string>& options_map) {
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
                utils::os::key current_key = utils::os::key_from_string(current_selection);

                if (utils::imgui::key_combobox(id.c_str(), &current_key)) {
                    current_selection = utils::os::key_to_string(current_key);
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
            case mods::mod_option_type::integer: {
                int num = std::stoi(current_selection);
                if (ImGui::InputInt(id.c_str(), &num)) {
                    current_selection = std::to_string(num);
                }
                break;
            }
            case mods::mod_option_type::floating: {
                float num = std::stof(current_selection);
                if (ImGui::InputFloat(id.c_str(), &num)) {
                    current_selection = std::format("{}", num);
                }
                break;
            }
            case mods::mod_option_type::multiple: {
                if (ImGui::BeginCombo(id.c_str(), current_selection.c_str())) {
                    for (const mods::mod_choice& choice : option.multiple_choice) {
                        bool is_selected = (current_selection == choice.display_name);

                        if (ImGui::Selectable(choice.display_name.c_str(), is_selected)) {
                            current_selection = choice.display_name;
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

        if (!option.default_choice.empty()) {
            if (utils::imgui::begin_tooltip()) {
                if (!option.default_choice.empty()) {
                    if (utils::imgui::begin_property_table("default")) {
                        utils::imgui::begin_property_row("Default");
                        ImGui::TextUnformatted(option.default_choice.c_str());
                        utils::imgui::end_property_row();
                        utils::imgui::end_property_table();
                    }
                }
                utils::imgui::end_tooltip();
            }
        }

        if (has_tooltip) {
            utils::imgui::set_help_marker(option.tooltip);
        }
    }

    void draw_mod_info() {
        const auto& discovered_mods = mods::manager::get().get_discovered_mods();
        auto mod_it = std::ranges::find_if(discovered_mods,
                                           [](const auto& m) { return m.id == selected_mod_id; });

        if (mod_it == discovered_mods.end()) {
            ImGui::TextDisabled("Select a mod to see its details.");
            return;
        }

        const mods::mod_info& mod = *mod_it;

        ImGui::PushFont(nullptr, ImGui::GetFontSize() * 1.35f);
        ImGui::TextUnformatted(mod.name.c_str());
        ImGui::PopFont();
        utils::imgui::set_tooltip(mod.id.c_str());
        
        std::string authors;
        for (size_t i = 0; i < mod.authors.size(); i++) {
            if (i > 0)
                authors += ", ";
            authors += mod.authors[i];
        }
 
        ImGui::TextDisabled("%s %s", ICON_MD_PEOPLE, authors.c_str());
        utils::imgui::set_tooltip("Authors");

        ImGui::TextDisabled("%s %s", ICON_MD_LOCAL_OFFER, mod.version.c_str());
        utils::imgui::set_tooltip("Version");

        if (!mod.api_compatible) {
            ImGui::TextColored(warning_color, ICON_MD_WARNING " Incompatible API version");
            utils::imgui::set_tooltip(api_warning_text(mod));
        }

        if (!mod.description.empty()) {
            ImGui::Spacing();
            ImGui::SeparatorText("Description");
            ImGui::TextWrapped("%s", mod.description.c_str());
        }

        if (!mod.options.empty()) {
            ImGui::Spacing();
            ImGui::SeparatorText("Options");
            auto& current_mod_state = temp_config.sledge.mod_states[mod.id];

            auto& options_map = current_mod_state.options;

            std::string table_id = mod.id + "_options";
            if (utils::imgui::begin_property_table(table_id.c_str())) {
                for (const mods::mod_option& option : mod.options) {
                    draw_mod_option(option, options_map);
                }
                utils::imgui::end_property_table();
            }
        }
    }
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

            draw_toolbar();
            ImGui::Spacing();

            float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;
            float footer_height = item_spacing_y + ImGui::GetFrameHeight();
            float child_height = ImGui::GetContentRegionAvail().y - footer_height - item_spacing_y;

            float mod_list_width = ImGui::GetContentRegionAvail().x * 0.35f;
            if (ImGui::BeginChild("mod_list", {mod_list_width, child_height},
                                  ImGuiChildFlags_Borders | ImGuiChildFlags_ResizeX,
                                  ImGuiWindowFlags_HorizontalScrollbar)) {
                draw_mod_list();
            }
            ImGui::EndChild();

            ImGui::SameLine();
            if (ImGui::BeginChild("mod_info", {ImGui::GetContentRegionAvail().x, child_height},
                                  ImGuiChildFlags_Borders)) {
                draw_mod_info();
            }
            ImGui::EndChild();

            float button_width = 110.0f * ImGui::GetStyle().FontScaleMain;
            float total_width = button_width * 2.0f + ImGui::GetStyle().ItemSpacing.x;

            ImGui::Spacing();
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x -
                                 total_width);

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