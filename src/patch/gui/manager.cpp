#include "manager.hpp"

#include "common/config.hpp"
#include "common/constants.hpp"
#include "common/utils/imgui.hpp"
#include "widgets/fps.hpp"
#include "widgets/position.hpp"
#include "patch/lua/manager.hpp"
#include "patch/rfg/game.hpp"

#include <imgui.h>
#include <memory>
#include <vector>
#include <spdlog/spdlog.h>

namespace gui {
    void manager::initialize() {
        register_widget(std::make_shared<fps_widget>());
        register_widget(std::make_shared<position_widget>());
    }

    void manager::draw_main_menu_bar() {
        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("Sledge")) {
                ImGui::BeginDisabled(*rfg::g_multiplayer());
                if (ImGui::MenuItem("Reload mods")) {
                    lua::manager::get().reload_mods();
                }
                ImGui::EndDisabled();

                if (utils::imgui::begin_help_marker()) {
                    ImGui::Text("Reloads all currently enabled mods and reparses their script "
                                "files. Clears all registered events, windows, and widgets.");
                    ImGui::TextDisabled(
                        "Intended for testing/debugging purposes. It is recommended to restart the "
                        "game instead of reloading mods in-game.");
                    utils::imgui::end_help_marker();
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Windows")) {
                if (config::get().sledge.imgui_demo_window) {
                    ImGui::MenuItem("ImGui demo", nullptr, &m_showing_demo_window);
                }

                for (const auto& window : windows) {
                    ImGui::MenuItem(window->title.c_str(), "", &window->open);

                    if (window->mod_info) {
                        if (utils::imgui::begin_tooltip()) {
                            if (utils::imgui::begin_property_table("window_mod_info")) {
                                utils::imgui::begin_property_row("Mod");
                                ImGui::TextUnformatted(window->mod_info->id.c_str());
                                utils::imgui::end_property_row();
                                utils::imgui::end_property_table();
                            }
                            utils::imgui::end_tooltip();
                        }
                    }
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Widgets")) {
                for (const auto& widget : widgets) {
                    if (ImGui::BeginMenu(widget->title.c_str())) {
                        ImGui::MenuItem("Visible", "", &widget->open);

                        ImGui::SeparatorText("Anchor");

                        if (ImGui::RadioButton("Top left",
                                               widget->anchor == panel_anchor::top_left))
                            widget->anchor = panel_anchor::top_left;
                        if (ImGui::RadioButton("Top right",
                                               widget->anchor == panel_anchor::top_right))
                            widget->anchor = panel_anchor::top_right;
                        if (ImGui::RadioButton("Bottom left",
                                               widget->anchor == panel_anchor::bottom_left))
                            widget->anchor = panel_anchor::bottom_left;
                        if (ImGui::RadioButton("Bottom right",
                                               widget->anchor == panel_anchor::bottom_right))
                            widget->anchor = panel_anchor::bottom_right;

                        ImGui::EndMenu();
                    }
                    if (widget->mod_info) {
                        if (utils::imgui::begin_tooltip()) {
                            if (utils::imgui::begin_property_table("window_mod_info")) {
                                utils::imgui::begin_property_row("Mod");
                                ImGui::TextUnformatted(widget->mod_info->id.c_str());
                                utils::imgui::end_property_row();
                                utils::imgui::end_property_table();
                            }
                            utils::imgui::end_tooltip();
                        }
                    }
                }
                ImGui::EndMenu();
            }

            ImGui::SameLine();
            auto version_cstr_size = ImGui::CalcTextSize(constants::version).x;
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x -
                                 version_cstr_size);
            ImGui::TextDisabled(constants::version);

            ImGui::EndMainMenuBar();
        }
    }

    void manager::draw_widgets() {
        ImGuiViewport* viewport = ImGui::GetMainViewport();

        std::unordered_map<panel_anchor, float> vertical_offsets = {
            {panel_anchor::top_left, viewport->WorkPos.y + 10.0f},
            {panel_anchor::top_right, viewport->WorkPos.y + 10.0f},
            {panel_anchor::bottom_left, viewport->WorkPos.y + viewport->WorkSize.y - 10.0f},
            {panel_anchor::bottom_right, viewport->WorkPos.y + viewport->WorkSize.y - 10.0f}};

        for (const auto& widget : widgets) {
            if (!widget->open) {
                continue;
            }

            ImVec2 pos(0.0f, vertical_offsets[widget->anchor]);
            ImVec2 pivot(0.0f, 0.0f);

            switch (widget->anchor) {
                case panel_anchor::top_left:
                    pos.x = viewport->WorkPos.x + widget->padding;
                    pivot = ImVec2(0.0f, 0.0f);
                    break;
                case panel_anchor::top_right:
                    pos.x = viewport->WorkPos.x + viewport->WorkSize.x - widget->padding;
                    pivot = ImVec2(1.0f, 0.0f);
                    break;
                case panel_anchor::bottom_left:
                    pos.x = viewport->WorkPos.x + widget->padding;
                    pivot = ImVec2(0.0f, 1.0f);
                    break;
                case panel_anchor::bottom_right:
                    pos.x = viewport->WorkPos.x + viewport->WorkSize.x - widget->padding;
                    pivot = ImVec2(1.0f, 1.0f);
                    break;
            }

            ImGui::SetNextWindowPos(pos, ImGuiCond_Always, pivot);
            if (ImGui::Begin(widget->title.c_str(), &widget->open,
                             ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground |
                                 ImGuiWindowFlags_NoInputs)) {
                widget->draw();
            }

            float height = ImGui::GetWindowSize().y;
            if (widget->anchor == panel_anchor::top_left ||
                widget->anchor == panel_anchor::top_right) {
                vertical_offsets[widget->anchor] += height;
            } else {
                vertical_offsets[widget->anchor] -= height;
            }

            ImGui::End();
        }
    };

    void manager::draw_windows() {
        for (const auto& window : windows) {
            if (!window->open)
                continue;

            auto center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Once, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(window->default_size, ImGuiCond_FirstUseEver);

            if (ImGui::Begin(window->title.c_str(), &window->open,
                             window->flags | ImGuiWindowFlags_NoCollapse)) {
                window->draw();
            }
            ImGui::End();
        }
    }

    void manager::draw() {
        draw_widgets();

        if (!g_show_overlay)
            return;

        draw_main_menu_bar();

        if (m_showing_demo_window)
            ImGui::ShowDemoWindow();

        draw_windows();
    }

    void manager::register_window(std::shared_ptr<panel> window) {
        windows.emplace_back(std::move(window));
    }

    void manager::register_widget(std::shared_ptr<panel> widget) {
        widgets.emplace_back(std::move(widget));
    }

    void manager::clear_mod_panels() {
        std::erase_if(windows, [](const auto& w) { return w->mod_info.has_value(); });
        std::erase_if(widgets, [](const auto& w) { return w->mod_info.has_value(); });
    }

    bool manager::wants_mouse() const { return g_show_overlay && ImGui::GetIO().WantCaptureMouse; }

    bool manager::wants_keyboard() const {
        return g_show_overlay && ImGui::GetIO().WantCaptureKeyboard;
    }

    bool manager::is_input_required() const {
        return g_show_overlay || wants_mouse() || wants_keyboard();
    }

    void panel::draw() {
        if (!draw_function || !draw_function->valid() || lua::manager::get().is_loading() ||
            *rfg::g_multiplayer()) {
            return;
        }

        auto result = lua::manager::get().execute_function(*draw_function);
        if (!result.valid()) {
            sol::error err = result;
            spdlog::error("[{}] Failed to draw panel: {}", title, err.what());
            this->open = false;
        }
    }
}
