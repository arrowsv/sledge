#include "gui.hpp"

#include "launcher.hpp"
#include "common/config.hpp"
#include "common/constants.hpp"
#include "common/mods.hpp"
#include "common/utils/imgui.hpp"
#include "common/utils/os.hpp"

#include <GL/gl.h>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <magic_enum.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace launcher::gui {
config gui_config;
std::string selected_mod_id = "";

static unsigned char background_picture_data[] = {
#include "background_picture.png.h"
};

static unsigned char background_overlay_data[] = {
#include "background_overlay.png.h"
};

static GLuint background_overlay_id = 0;
static GLuint background_picture_id = 0;

void load_background_textures() {
    {
        int image_width = 0;
        int image_height = 0;

        unsigned char* image_data =
            stbi_load_from_memory(background_picture_data, sizeof(background_picture_data),
                                  &image_width, &image_height, NULL, 4);

        glGenTextures(1, &background_picture_id);
        glBindTexture(GL_TEXTURE_2D, background_picture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);
    }

    {
        int image_width = 0;
        int image_height = 0;

        unsigned char* image_data =
            stbi_load_from_memory(background_overlay_data, sizeof(background_overlay_data),
                                  &image_width, &image_height, NULL, 4);

        glGenTextures(1, &background_overlay_id);
        glBindTexture(GL_TEXTURE_2D, background_overlay_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, image_data);
        stbi_image_free(image_data);
    }
}

void draw_options_modal() {
    if (ImGui::BeginPopupModal("Options", NULL,
                               ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize)) {
        utils::imgui::key_combobox("Sledge menu key", &gui_config.open_key);

        ImGui::InputInt("FPS limit", (int*)&gui_config.fps_limit);
        ImGui::SetItemTooltip("To prevent engine issues, the recommended values are 60 or 120.");

        ImGui::Checkbox("Skip startup videos", &gui_config.skip_startup_videos);

        ImGui::Separator();

        float item_spacing = ImGui::GetStyle().ItemSpacing.x;
        float available_width = ImGui::GetContentRegionAvail().x;

        int button_count = 2;
        float button_width = (available_width - (item_spacing * (button_count - 1))) / button_count;

        if (ImGui::Button("Apply", {button_width, 0})) {
            config::get() = gui_config;
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

void draw_mods_modal() {
    ImVec2 main_window_size = ImGui::GetMainViewport()->Size;
    float padding = ImGui::GetStyle().WindowPadding.x;
    ImVec2 mods_modal_size = {main_window_size.x - (padding * 2.0f),
                              main_window_size.y - (padding * 2.0f)};
    ImGui::SetNextWindowSize(mods_modal_size, ImGuiCond_Always);
    if (ImGui::BeginPopupModal("Mods", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
        float total_width = ImGui::GetContentRegionAvail().x;
        float total_height = ImGui::GetContentRegionAvail().y;

        float item_spacing_x = ImGui::GetStyle().ItemSpacing.x;
        float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;

        float button_height = ImGui::GetFrameHeight();

        float bottom_section_height = item_spacing_y + item_spacing_y + button_height;
        float child_height = total_height - bottom_section_height;

        float mod_list_width = 180;
        float mod_info_width = total_width - mod_list_width - item_spacing_x;

        auto discovered_mods = mods::manager::get().get_discovered_mods();

        if (ImGui::BeginChild("mod_list", {mod_list_width, child_height}, ImGuiChildFlags_Borders,
                              ImGuiWindowFlags_HorizontalScrollbar)) {
            for (const auto& mod : discovered_mods) {
                auto state = gui_config.mod_states.find(mod.id);
                if (state == gui_config.mod_states.end())
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
        if (ImGui::BeginChild("mod_info", {mod_info_width, child_height}, ImGuiChildFlags_Borders,
                              ImGuiWindowFlags_HorizontalScrollbar)) {
            auto mod_it = std::ranges::find_if(
                discovered_mods, [](const auto& m) { return m.id == selected_mod_id; });

            if (mod_it != discovered_mods.end()) {
                const mods::mod_info& mod = *mod_it;

                ImGui::Text("%s", mod.name.c_str());
                ImGui::Text("Version: %s", mod.version.c_str());
                ImGui::Text("Author: %s", mod.author.c_str());

                if (!mod.description.empty()) {
                    ImGui::SeparatorText("Description");
                    ImGui::TextWrapped("%s", mod.description.c_str());
                }

                if (!mod.options.empty()) {
                    ImGui::SeparatorText("Options");
                    auto& current_mod_state = gui_config.mod_states[mod.id];

                    for (const mods::mod_option& option : mod.options) {
                        std::string& current_selection = current_mod_state.options[option.name];

                        switch (option.type) {
                        case mods::mod_option_type::custom: {
                            ImGui::InputText(option.name.c_str(), &current_selection);
                            break;
                        }
                        case mods::mod_option_type::key: {
                            utils::os::key current_key =
                                utils::os::key_from_string(current_selection);
                            if (utils::imgui::key_combobox(option.name.c_str(), &current_key)) {
                                current_selection = utils::os::key_to_string(current_key);
                            }
                            break;
                        }
                        case mods::mod_option_type::checkbox: {
                            bool is_checked = (current_selection == "true");
                            if (ImGui::Checkbox(option.name.c_str(), &is_checked)) {
                                current_selection = is_checked ? "true" : "false";
                            }
                            break;
                        }
                        case mods::mod_option_type::multiple: {
                            if (ImGui::BeginCombo(option.name.c_str(), current_selection.c_str())) {
                                for (int i = 0; i < option.choice_multiple.size(); i++) {
                                    const std::string& val = option.choice_multiple[i];
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
                    }
                }
            } else {
                ImGui::TextDisabled("No mod selected.");
            }
        }
        ImGui::EndChild();

        float item_spacing = ImGui::GetStyle().ItemSpacing.x;
        float available_width = ImGui::GetContentRegionAvail().x;

        int button_count = 3;
        float button_width = (available_width - (item_spacing * (button_count - 1))) / button_count;

        ImGui::Spacing();
        if (ImGui::Button("Apply", {button_width, 0})) {
            config::get() = gui_config;
            config::get().save();
            ImGui::CloseCurrentPopup();
        }

        ImGui::SameLine();
        if (ImGui::Button("Rescan", {button_width, 0})) {
            auto sledge_directory = utils::os::get_module_directory(GetModuleHandleA(nullptr));

            config::get().initialize(sledge_directory);
            mods::manager::get().initialize(sledge_directory / "mods");
            selected_mod_id = "";
            gui_config = config::get();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", {button_width, 0})) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
}

void draw() {
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::GetBackgroundDrawList()->AddImage(
        (ImTextureID)(intptr_t)background_picture_id, viewport->Pos,
        ImVec2(viewport->Pos.x + viewport->Size.x, viewport->Pos.y + viewport->Size.y));

    ImGui::GetBackgroundDrawList()->AddImage(
        (ImTextureID)(intptr_t)background_overlay_id, viewport->Pos,
        ImVec2(viewport->Pos.x + viewport->Size.x, viewport->Pos.y + viewport->Size.y));

    ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
    ImGui::SetNextWindowPos(ImVec2{0, 0});

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Main", NULL,
                 ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoBackground);
    ImGui::PopStyleVar(2);

    float available_height = ImGui::GetContentRegionAvail().y;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + available_height - ImGui::GetFrameHeight());

    if (ImGui::Button("Play")) {
        launcher::select_play();
    }
    ImGui::SameLine();
    if (ImGui::Button("Play (vanilla)")) {
        launcher::select_play_vanilla();
    }
    ImGui::SameLine();
    if (ImGui::Button("Options")) {
        gui_config = config::get();
        ImGui::OpenPopup("Options");
    }
    ImGui::SameLine();
    if (ImGui::Button("Mods")) {
        gui_config = config::get();
        ImGui::OpenPopup("Mods");
    }

    std::string version_str = "Version: " + std::string(constants::version);
    const char* version_cstr = version_str.c_str();
    auto version_cstr_size = ImGui::CalcTextSize(version_cstr).x;

    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x -
                         version_cstr_size);
    ImGui::TextDisabled("%s", version_cstr);

    draw_options_modal();
    draw_mods_modal();

    ImGui::End();
}

} // namespace launcher::gui
