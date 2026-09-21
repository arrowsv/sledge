#include "gui.hpp"

#include "common/utils/imgui.hpp"

#include <imgui.h>
#include <imgui_stdlib.h>
#include <sol/sol.hpp>
#include <spdlog/spdlog.h>

namespace lua::bindings::sledge {

    void bind_utility(sol::table& table) {
        table["set_next_item_width"] = [](float width) { ImGui::SetNextItemWidth(width); };

        table["push_item_width"] = [](float width) { ImGui::PushItemWidth(width); };
        table["pop_item_width"] = &ImGui::PopItemWidth;

        table["get_available_space"] = []() {
            ImVec2 available_space = ImGui::GetContentRegionAvail();
            return std::make_tuple(available_space.x, available_space.y);
        };

        table["begin_disabled"] = &ImGui::BeginDisabled;
        table["end_disabled"] = &ImGui::EndDisabled;
    }

    void bind_layout(sol::table& table) {
        table["separator"] = [](sol::optional<std::string> label) {
            if (label.has_value()) {
                ImGui::SeparatorText(label->c_str());
            } else {
                ImGui::Separator();
            }
        };
        table["same_line"] = []() { ImGui::SameLine(); };
        table["new_line"] = &ImGui::NewLine;
        table["spacing"] = &ImGui::Spacing;
        table["indent"] = [](sol::optional<float> width) { ImGui::Indent(width.value_or(0)); };
        table["unindent"] = [](sol::optional<float> width) { ImGui::Unindent(width.value_or(0)); };
        table["bullet"] = &ImGui::Bullet;
    }

    void bind_text(sol::table& table) {
        table["text"] = [](const std::string& text) { ImGui::Text("%s", text.c_str()); };

        table["text_disabled"] = [](const std::string& text) {
            ImGui::TextDisabled("%s", text.c_str());
        };

        table["text_wrapped"] = [](const std::string& text) {
            ImGui::TextWrapped("%s", text.c_str());
        };

        table["text_bullet"] = [](const std::string& text) {
            ImGui::BulletText("%s", text.c_str());
        };
    }

    void bind_widget(sol::table& table) {
        table["button"] = [](const std::string& label, sol::function on_pressed,
                             sol::optional<sol::table> options) {
            float width = 0.0;
            float height = 0.0;

            if (options) {
                width = options->get_or("width", 0.0);
                height = options->get_or("height", 0.0);
            }

            bool pressed = ImGui::Button(label.c_str(), {width, height});
            if (pressed) {
                on_pressed();
            }
        };

        table["checkbox"] = sol::overload(
            [](bool value, sol::function on_change) {
                bool new_value = value;
                bool changed = ImGui::Checkbox("##", &new_value);
                if (changed) {
                    on_change(new_value);
                }
            },
            [](const std::string& label, bool value, sol::function on_change) {
                bool new_value = value;
                bool changed = ImGui::Checkbox(label.c_str(), &new_value);
                if (changed) {
                    on_change(new_value);
                }
            });
    }

    void bind_tooltip(sol::table& table) {
        table["set_tooltip"] = utils::imgui::set_tooltip;
        table["tooltip"] = [](sol::function body) {
            if (utils::imgui::begin_tooltip()) {
                body();
                utils::imgui::end_tooltip();
            }
        };

        table["set_help_marker"] = &utils::imgui::set_help_marker;
        table["help_marker"] = [](sol::function body) {
            if (utils::imgui::begin_help_marker()) {
                body();
                utils::imgui::end_help_marker();
            }
        };
    }

    void bind_tab(sol::table& table) {
        table["tab_bar"] = [](const std::string& id, sol::function body) {
            if (ImGui::BeginTabBar(id.c_str())) {
                body();
                ImGui::EndTabBar();
            }
        };

        table["tab_item"] = [](const std::string& label, sol::function body) {
            if (ImGui::BeginTabItem(label.c_str())) {
                body();
                ImGui::EndTabItem();
            }
        };
    }

    void bind_input(sol::table& table) {
        table["input_text"] = sol::overload(
            [](std::string text, sol::function on_change) {
                std::string new_value = text;
                bool changed = ImGui::InputText("##", &new_value);
                if (changed) {
                    on_change(new_value);
                }
            },
            [](const std::string& label, std::string text, sol::function on_change) {
                std::string new_value = text;
                bool changed = ImGui::InputText(label.c_str(), &new_value);
                if (changed) {
                    on_change(new_value);
                }
            });

        table["input_int"] = sol::overload(
            [](int value, sol::function on_change) {
                int new_value = value;
                bool changed = ImGui::InputInt("##", &new_value);
                if (changed) {
                    on_change(new_value);
                }
            },
            [](const std::string& label, int value, sol::function on_change) {
                int new_value = value;
                bool changed = ImGui::InputInt(label.c_str(), &new_value);
                if (changed) {
                    on_change(new_value);
                }
            });

        table["input_float"] = sol::overload(
            [](float value, sol::function on_change) {
                float new_value = value;
                bool changed = ImGui::InputFloat("##", &new_value);
                if (changed) {
                    on_change(new_value);
                }
            },
            [](const std::string& label, float value, sol::function on_change) {
                float new_value = value;
                bool changed = ImGui::InputFloat(label.c_str(), &new_value);
                if (changed) {
                    on_change(new_value);
                }
            });
    }

    void bind_input_slider(sol::table& table) {
        table["slider_int"] = sol::overload(
            [](int value, int min, int max, sol::function on_change) {
                int new_value = value;
                bool changed = ImGui::SliderInt("##", &new_value, min, max);
                if (changed) {
                    on_change(new_value);
                }
            },
            [](const std::string& label, int value, int min, int max, sol::function on_change) {
                int new_value = value;
                bool changed = ImGui::SliderInt(label.c_str(), &new_value, min, max);
                if (changed) {
                    on_change(new_value);
                }
            });

        table["slider_float"] = sol::overload(
            [](float value, float min, float max, sol::function on_change) {
                float new_value = value;
                bool changed = ImGui::SliderFloat("##", &new_value, min, max);
                if (changed) {
                    on_change(new_value);
                }
            },
            [](const std::string& label, float value, float min, float max,
               sol::function on_change) {
                float new_value = value;
                bool changed = ImGui::SliderFloat(label.c_str(), &new_value, min, max);
                if (changed) {
                    on_change(new_value);
                }
            });
    }

    void bind_input_slider(sol::table& table, sol::state_view& lua) {
        table["slider_int"] = [](const std::string& label, int value, int min, int max) {
            bool changed = ImGui::SliderInt(label.c_str(), &value, min, max);
            return std::make_tuple(value, changed);
        };

        table["slider_float"] = [](const std::string& label, float value, float min, float max) {
            bool changed = ImGui::SliderFloat(label.c_str(), &value, min, max);
            return std::make_tuple(value, changed);
        };
    }

    void bind_gui(sol::state_view& lua) {
        auto table = lua["gui"].get_or_create<sol::table>();

        bind_utility(table);
        bind_layout(table);
        bind_text(table);
        bind_widget(table);
        bind_tooltip(table);
        bind_tab(table);
        bind_input(table);
        bind_input_slider(table);
        bind_property_table(table);
    }
}
