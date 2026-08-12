#include "gui.hpp"

#include "common/constants.hpp"
#include "common/utils/imgui.hpp"
#include "overlays/fps.hpp"
#include "overlays/position.hpp"
#include "patch/lua/manager.hpp"
#include "patch/rfg/game.hpp"

#include <imgui.h>
#include <memory>
#include <vector>

namespace gui {
std::vector<std::shared_ptr<panel>> core_windows{};
std::vector<std::shared_ptr<panel>> core_overlays{};

std::vector<std::shared_ptr<mod_panel>> mod_windows{};
std::vector<std::shared_ptr<mod_panel>> mod_overlays{};

void manager::initialize() {
    register_core_overlay(std::make_shared<fps_overlay>());
    register_core_overlay(std::make_shared<position_overlay>());
}

void manager::draw_main_menu_bar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Sledge")) {
            ImGui::MenuItem("Demo window", "", &m_showing_demo_window);

            ImGui::BeginDisabled(*rfg::g_multiplayer());
            if (ImGui::MenuItem("Reload mods")) {
                lua::manager::get().reload_mods();
            }
            ImGui::EndDisabled();
            if (utils::imgui::begin_help_marker()) {
                ImGui::Text("Reloads all currently enabled mods and reparses their script files.");
                ImGui::Text("Clears all registered events, windows, and overlays.");
                ImGui::TextDisabled("Intended for testing/debugging purposes.");
                ImGui::TextDisabled(
                    "It is recommended to restart the game instead of reloading mods in-game.");
                utils::imgui::end_help_marker();
            }

            for (auto& window : core_windows)
                ImGui::MenuItem(window->title.c_str(), "", &window->open);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Windows")) {
            for (const auto& window : mod_windows) {
                ImGui::MenuItem(window->title.c_str(), "", &window->open);
                ImGui::SameLine();
                ImGui::TextDisabled("(%s)", window->mod_info.id.c_str());
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Overlays")) {
            for (const auto& overlay : core_overlays) {
                ImGui::MenuItem(overlay->title.c_str(), "", &overlay->open);
            }
            for (const auto& overlay : mod_overlays) {
                ImGui::MenuItem(overlay->title.c_str(), "", &overlay->open);
                ImGui::SameLine();
                ImGui::TextDisabled("(%s)", overlay->mod_info.id.c_str());
            }
            ImGui::EndMenu();
        }

        std::string version_str = "Version: " + std::string(constants::version);
        const char* version_cstr = version_str.c_str();
        auto version_cstr_size = ImGui::CalcTextSize(version_cstr).x;

        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x -
                             version_cstr_size);
        ImGui::TextDisabled("%s", version_cstr);

        ImGui::EndMainMenuBar();
    }
}

void manager::draw_dockspace() {
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoBringToFrontOnFocus |
                                    ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImVec2 dockspaceSize = viewport->WorkSize;
    ImGui::SetNextWindowSize(dockspaceSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace parent window", nullptr, window_flags);
    ImGui::PopStyleVar(3);

    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
        ImGuiID dockspaceId = ImGui::GetID("Editor dockspace");
        ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspace_flags);
    }

    ImGui::End();
}

void manager::draw() {
    auto draw_panels = [](const auto& panel_list) {
        for (const auto& panel : panel_list) {
            if (!panel->open)
                continue;

            auto center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Once, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(panel->default_size, ImGuiCond_FirstUseEver);

            if (ImGui::Begin(panel->title.c_str(), &panel->open,
                             panel->flags | ImGuiWindowFlags_NoCollapse))
                panel->draw();

            ImGui::End();
        }
    };

    draw_panels(core_overlays);
    draw_panels(mod_overlays);

    if (!g_show_windows)
        return;

    draw_main_menu_bar();
    // draw_dockspace();

    if (m_showing_demo_window)
        ImGui::ShowDemoWindow();

    draw_panels(core_windows);
    draw_panels(mod_windows);
}

void manager::register_core_window(std::shared_ptr<panel> window) {
    core_windows.emplace_back(window);
}
void manager::register_core_overlay(std::shared_ptr<panel> overlay) {
    core_overlays.emplace_back(overlay);
}
void manager::register_mod_window(std::shared_ptr<mod_panel> window) {
    mod_windows.emplace_back(window);
}
void manager::register_mod_overlay(std::shared_ptr<mod_panel> overlay) {
    mod_overlays.emplace_back(overlay);
}

void manager::clear_mod_panels() {
    mod_windows.clear();
    mod_overlays.clear();
}

void mod_panel::draw() {
    if (!draw_function.valid() || *rfg::g_multiplayer() || lua::manager::get().is_loading())
        return;

    auto result = lua::manager::get().execute_function(draw_function);
    if (!result.valid()) {
        sol::error err = result;
        PLOG_ERROR << "[" << mod_info.name << "][" << title << " Error] " << err.what();
        this->open = false;
    }
}
} // namespace gui
