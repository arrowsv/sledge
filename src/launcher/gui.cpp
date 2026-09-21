#include "gui.hpp"

#include "launcher.hpp"
#include "common/config.hpp"
#include "common/constants.hpp"
#include "common/mods.hpp"
#include "common/utils/imgui.hpp"
#include "modals/mods.hpp"
#include "modals/options.hpp"

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

        float available_height = ImGui::GetContentRegionAvail().y;
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + available_height - ImGui::GetFrameHeight());

        if (ImGui::Button(ICON_MS_PLAY_ARROW " Play")) {
            launcher::select_play();
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_MS_PLAY_ARROW "Play (vanilla)")) {
            launcher::select_play_vanilla();
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_MS_SETTINGS " Options")) {
            gui_config = config::get();
            ImGui::OpenPopup("Options");
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_MS_EXTENSION " Mods")) {
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

}
