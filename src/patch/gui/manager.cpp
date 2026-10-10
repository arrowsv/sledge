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

const float widget_padding = 10.0f;

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
                    ImGui::MenuItem(window->title.c_str(), "", &window->options.open);

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
                        ImGui::MenuItem("Visible", "", &widget->options.open);

                        ImGui::SeparatorText("Anchor");

                        if (ImGui::RadioButton("Top left",
                                               widget->options.anchor == panel_anchor::top_left))
                            widget->options.anchor = panel_anchor::top_left;
                        if (ImGui::RadioButton("Top right",
                                               widget->options.anchor == panel_anchor::top_right))
                            widget->options.anchor = panel_anchor::top_right;
                        if (ImGui::RadioButton("Bottom left",
                                               widget->options.anchor == panel_anchor::bottom_left))
                            widget->options.anchor = panel_anchor::bottom_left;
                        if (ImGui::RadioButton("Bottom right", widget->options.anchor ==
                                                                   panel_anchor::bottom_right))
                            widget->options.anchor = panel_anchor::bottom_right;

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
            auto version_cstr_size = ImGui::CalcTextSize(constants::sledge_version.to_string().c_str()).x;
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x -
                                 version_cstr_size);
            ImGui::TextDisabled("%s", constants::sledge_version.to_string().c_str());

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
            if (!widget->options.open) {
                continue;
            }

            ImVec2 pos(0.0f, vertical_offsets[widget->options.anchor]);
            ImVec2 pivot(0.0f, 0.0f);

            switch (widget->options.anchor) {
                case panel_anchor::top_left:
                    pos.x = viewport->WorkPos.x + widget_padding;
                    pivot = ImVec2(0.0f, 0.0f);
                    break;
                case panel_anchor::top_right:
                    pos.x = viewport->WorkPos.x + viewport->WorkSize.x - widget_padding;
                    pivot = ImVec2(1.0f, 0.0f);
                    break;
                case panel_anchor::bottom_left:
                    pos.x = viewport->WorkPos.x + widget_padding;
                    pivot = ImVec2(0.0f, 1.0f);
                    break;
                case panel_anchor::bottom_right:
                    pos.x = viewport->WorkPos.x + viewport->WorkSize.x - widget_padding;
                    pivot = ImVec2(1.0f, 1.0f);
                    break;
            }

            ImGui::SetNextWindowPos(pos, ImGuiCond_Always, pivot);
            if (ImGui::Begin(widget->title.c_str(), &widget->options.open,
                             ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove |
                                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground |
                                 ImGuiWindowFlags_NoInputs)) {
                widget->draw();
            }

            float height = ImGui::GetWindowSize().y;
            if (widget->options.anchor == panel_anchor::top_left ||
                widget->options.anchor == panel_anchor::top_right) {
                vertical_offsets[widget->options.anchor] += height;
            } else {
                vertical_offsets[widget->options.anchor] -= height;
            }

            ImGui::End();
        }
    };

    void manager::draw_windows() {
        for (const auto& window : windows) {
            if (!window->options.open)
                continue;

            auto center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Once, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(window->options.default_size, ImGuiCond_FirstUseEver);

            if (ImGui::Begin(window->title.c_str(), &window->options.open,
                             window->options.flags | ImGuiWindowFlags_NoCollapse)) {
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
        if (!options.draw_function || !options.draw_function->valid() ||
            lua::manager::get().is_loading() || *rfg::g_multiplayer()) {
            return;
        }

        if (options.requires_gameplay && rfg::gameseq_get_state() != rfg::GS_GAMEPLAY) {
            ImGui::TextDisabled("This panel requires the player to be in gameplay.");
            return;
        }

        auto result = lua::manager::get().execute_function(*options.draw_function);
        if (!result.valid()) {
            sol::error err = result;
            spdlog::error("[{}] Failed to draw panel: {}", title, err.what());
            this->options.open = false;
        }
    }
}
