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

        float available_height = ImGui::GetContentRegionAvail().y;
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + available_height - ImGui::GetFrameHeight());

        if (ImGui::Button(ICON_MD_PLAY_ARROW " Play")) {
            launch();
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_MD_PLAY_ARROW " Play (vanilla)")) {
            launch(true);
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_MD_SETTINGS " Options")) {
            ImGui::OpenPopup("Options");
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_MD_EXTENSION " Mods")) {
            ImGui::OpenPopup("Mods");
        }
        ImGui::SameLine();
        if (ImGui::Button(ICON_MD_OPEN_IN_BROWSER " GitHub")) {
            ShellExecuteW(0, L"open", L"https://github.com/arrowsv/sledge", NULL, NULL,
                          SW_SHOWDEFAULT);
        }

        auto version_size = ImGui::CalcTextSize(constants::version).x;

        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x -
                             version_size);
        ImGui::TextDisabled(constants::version);

        draw_options_modal();
        draw_mods_modal();

        ImGui::End();
    }
}
