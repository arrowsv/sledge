#include "gui.hpp"

#include "injector.hpp"
#include "common/assets/fonts/icons.hpp"
#include "common/constants.hpp"
#include "modals/mods.hpp"
#include "modals/options.hpp"

#include <GL/gl.h>
#include <imgui.h>
#include <spdlog/spdlog.h>
#include <stb_image.h>

namespace {
    unsigned char background_picture_data[] = {
#include "background_picture.png.h"
    };

    unsigned char background_overlay_data[] = {
#include "background_overlay.png.h"
    };

    enum class play_choices { sledge, vanilla, count };

    const char* play_choices_names[] = {"Sledge", "Vanilla"};
    play_choices selected_play_choice = play_choices::sledge;

    float column_height = 0.0f;

    GLuint background_overlay_id = 0;
    GLuint background_picture_id = 0;

    GLuint load_texture_from_memory(const unsigned char* data, int data_size) {
        int image_width = 0;
        int image_height = 0;

        unsigned char* image_data =
            stbi_load_from_memory(data, data_size, &image_width, &image_height, NULL, 4);

        if (!image_data) {
            spdlog::error("Failed to load texture: {}", stbi_failure_reason());
            return 0;
        }

        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, image_data);

        stbi_image_free(image_data);
        return texture_id;
    }
}

namespace gui {
    void load_background_textures() {
        background_picture_id =
            load_texture_from_memory(background_picture_data, sizeof(background_picture_data));
        background_overlay_id =
            load_texture_from_memory(background_overlay_data, sizeof(background_overlay_data));
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
                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                         ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
        ImGui::PopStyleVar(2);

        bool open_options = false;
        bool open_mods = false;

        ImGuiIO& io = ImGui::GetIO();
        ImGui::SetCursorPos({io.DisplaySize.x * 0.11f, (io.DisplaySize.y - column_height) * 0.5f});
        ImGui::BeginChild("##column", {227, 0}, ImGuiChildFlags_AutoResizeY,
                          ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

        const float full = -FLT_MIN;
        const float half =
            (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.y) * 0.5f;

        ImGui::SetNextItemWidth(full);

        std::string selected_play_choice_str =
            "Profile: " + std::string(play_choices_names[(int)selected_play_choice]);
        if (ImGui::BeginCombo("##Play choice", selected_play_choice_str.c_str())) {
            for (int n = 0; n < (int)play_choices::count; n++) {
                bool is_selected = ((int)selected_play_choice == n);
                if (ImGui::Selectable(play_choices_names[n], is_selected)) {
                    selected_play_choice = (play_choices)n;
                }

                if (is_selected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        if (ImGui::Button(ICON_MD_PLAY_ARROW " Play", {full, 52})) {
            if (selected_play_choice == play_choices::sledge) {
                launch();
            } else {
                launch(true);
            }
        }

        if (ImGui::Button(ICON_MD_SETTINGS " Options", {half, 34})) {
            open_options = true;
        }
        ImGui::SameLine(0.0, ImGui::GetStyle().ItemSpacing.y);
        if (ImGui::Button(ICON_MD_EXTENSION " Mods", {half, 34})) {
            open_mods = true;
        }

        if (ImGui::Button(ICON_MD_OPEN_IN_NEW " Documentation", {full, 24})) {
            std::string readthedocs_link =
                std::format("https://sledge.readthedocs.io/en/{}/", constants::version);
            ShellExecuteA(0, "open", readthedocs_link.c_str(), NULL, NULL, SW_SHOWDEFAULT);
        }

        if (ImGui::Button(ICON_MD_OPEN_IN_NEW " FactionFiles mods", {full, 24})) {
            ShellExecuteA(0, "open",
                          "https://www.factionfiles.com/ff.php?action=files&file_category=52", NULL,
                          NULL, SW_SHOWDEFAULT);
        }

        if (ImGui::Button(ICON_MD_OPEN_IN_NEW " Discord", {full, 24})) {
            ShellExecuteA(0, "open", "https://discord.gg/factionfiles", NULL, NULL, SW_SHOWDEFAULT);
        }

        ImGui::EndChild();

        column_height = ImGui::GetItemRectSize().y;

        auto version_size = ImGui::CalcTextSize(constants::version);
        ImGui::SetCursorPos(
            {io.DisplaySize.x - version_size.x - 12, io.DisplaySize.y - version_size.y - 12});
        ImGui::TextDisabled(constants::version);

        if (open_options) {
            ImGui::OpenPopup("Options");
        }

        if (open_mods) {
            ImGui::OpenPopup("Mods");
        }

        draw_options_modal();
        draw_mods_modal();

        ImGui::End();
    }
}
