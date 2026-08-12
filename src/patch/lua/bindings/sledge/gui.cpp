#include "gui.hpp"
#include "common/utils/imgui.hpp"

#include <imgui.h>
#include <imgui_stdlib.cpp>
#include <imgui_stdlib.h>
#include <plog/Log.h>
#include <sol/sol.hpp>

namespace lua::bindings::sledge {

void bind_utility(sol::table& table) {
    table["set_next_item_width"] = [](float width) { ImGui::SetNextItemWidth(width); };

    table["push_item_width"] = [](float width) { ImGui::PushItemWidth(width); };

    table["pop_item_width"] = &ImGui::PopItemWidth;

    table["get_available_space"] = []() {
        ImVec2 available_space = ImGui::GetContentRegionAvail();
        return std::make_tuple(available_space.x, available_space.y);
    };

    table["get_cursor_screen_position"] = []() {
        ImVec2 position = ImGui::GetCursorScreenPos();
        return std::make_tuple(position.x, position.y);
    };

    table["begin_disabled"] = &ImGui::BeginDisabled;
    table["end_disabled"] = &ImGui::EndDisabled;
}

void bind_layout(sol::table& table) {
    table["separator"] = &ImGui::Separator;

    table["separator_text"] = [](const std::string& label) {
        return ImGui::SeparatorText(label.c_str());
    };

    table["same_line"] = []() { ImGui::SameLine(); };

    table["new_line"] = &ImGui::NewLine;

    table["spacing"] = &ImGui::Spacing;

    table["dummy"] = [](float width, float height) { ImGui::Dummy({width, height}); };

    table["indent"] =
        sol::overload([]() { ImGui::Indent(); }, [](float width) { ImGui::Indent(width); });

    table["unindent"] =
        sol::overload([]() { ImGui::Unindent(); }, [](float width) { ImGui::Unindent(width); });

    table["bullet"] = &ImGui::Bullet;
}

void bind_text(sol::table& table) {
    table["text"] = [](const std::string& text) { ImGui::Text("%s", text.c_str()); };

    table["text_disabled"] = [](const std::string& text) {
        ImGui::TextDisabled("%s", text.c_str());
    };
    table["text_wrapped"] = [](const std::string& text) { ImGui::TextWrapped("%s", text.c_str()); };

    table["text_bullet"] = [](const std::string& text) { ImGui::BulletText("%s", text.c_str()); };

    table["label_text"] = [](const std::string& label, const std::string& text) {
        ImGui::LabelText(label.c_str(), "%s", text.c_str());
    };
}

void bind_widget(sol::table& table) {
    table["button"] = [](const std::string& label, sol::optional<float> width,
                         sol::optional<float> height) {
        return ImGui::Button(label.c_str(), {width.value_or(0), height.value_or(0)});
    };

    table["button_small"] = [](const std::string& label) {
        return ImGui::SmallButton(label.c_str());
    };

    table["button_invisible"] = [](const std::string& label, float width, float height) {
        return ImGui::InvisibleButton(label.c_str(), {width, height});
    };

    table["button_arrow"] = [](const std::string& label, ImGuiDir direction) {
        return ImGui::ArrowButton(label.c_str(), direction);
    };

    table["checkbox"] = [](const std::string& label, bool value) {
        bool changed = ImGui::Checkbox(label.c_str(), &value);
        return std::make_tuple(value, changed);
    };
}

void bind_tooltip(sol::table& table) {
    table["set_tooltip"] = [](const std::string& text) {
        ImGui::SetItemTooltip("%s", text.c_str());
    };

    table["begin_tooltip"] = &ImGui::BeginItemTooltip;

    table["end_tooltip"] = &ImGui::EndTooltip;

    table["set_help_marker"] = &utils::imgui::set_help_marker;

    table["begin_help_marker"] = &utils::imgui::begin_help_marker;

    table["end_help_marker"] = &utils::imgui::end_help_marker;
}

void bind_popup(sol::table& table) {
    table["begin_popup"] = [](const std::string& id) { return ImGui::BeginPopup(id.c_str()); };
    table["end_popup"] = &ImGui::EndPopup;

    table["open_popup"] = [](const std::string& id) { ImGui::OpenPopup(id.c_str()); };
    table["close_current_popup"] = &ImGui::CloseCurrentPopup;
}

void bind_menu(sol::table& table) {
    table["begin_menu_bar"] = &ImGui::BeginMenuBar;
    table["end_menu_bar"] = &ImGui::EndMenuBar;

    table["begin_menu"] =
        sol::overload([](const std::string& label) { return ImGui::BeginMenu(label.c_str()); },
                      [](const std::string& label, bool enabled) {
                          return ImGui::BeginMenu(label.c_str(), enabled);
                      });
    table["end_menu"] = &ImGui::EndMenu;

    table["menu_item"] =
        sol::overload([](const std::string& label) { return ImGui::MenuItem(label.c_str()); },
                      [](const std::string& label, bool selected) {
                          return ImGui::MenuItem(label.c_str(), NULL, selected);
                      });
}

void bind_tab(sol::table& table) {
    table["begin_tab_bar"] = [](const std::string& id) { return ImGui::BeginTabBar(id.c_str()); };

    table["end_tab_bar"] = &ImGui::EndTabBar;

    table["begin_tab_item"] = [](const std::string& label) {
        return ImGui::BeginTabItem(label.c_str());
    };

    table["end_tab_item"] = &ImGui::EndTabItem;
}

void bind_tree(sol::table& table) {
    table["begin_tree_node"] = [](const std::string& text) {
        return ImGui::TreeNode(text.c_str());
    };
    table["end_tree_node"] = &ImGui::TreePop;
    table["collapsing_header"] = [](const std::string& text) {
        return ImGui::CollapsingHeader(text.c_str());
    };
}

void bind_table(sol::table& table) {
    table["begin_table"] = [](const std::string& id, int columns) {
        return ImGui::BeginTable(id.c_str(), columns);
    };
    table["end_table"] = &ImGui::EndTable;

    table["table_next_row"] = []() { ImGui::TableNextRow(); };
    table["table_next_column"] = []() { ImGui::TableNextColumn(); };
}

void bind_input(sol::table& table, sol::state_view& lua) {
    table["input_text"] = [](const std::string& label, std::string text) {
        bool changed = ImGui::InputText(label.c_str(), &text);
        return std::make_tuple(text, changed);
    };

    table["input_text_hint"] = [](const std::string& label, const std::string& hint,
                                  std::string text) {
        bool changed = ImGui::InputTextWithHint(label.c_str(), hint.c_str(), &text);
        return std::make_tuple(text, changed);
    };

    table["input_int"] = [](const std::string& label, int value) {
        bool changed = ImGui::InputInt(label.c_str(), &value);
        return std::make_tuple(value, changed);
    };

    table["input_int_2"] = [&lua](const std::string& label, const sol::table& input_table) {
        int ints[2] = {input_table.get_or(1, 0), input_table.get_or(2, 0)};
        bool changed = ImGui::InputInt2(label.c_str(), ints);
        sol::table values = lua.create_table_with(1, ints[0], 2, ints[1]);
        return std::make_tuple(values, changed);
    };

    table["input_int_3"] = [&lua](const std::string& label, const sol::table& input_table) {
        int ints[3] = {input_table.get_or(1, 0), input_table.get_or(2, 0),
                       input_table.get_or(3, 0)};
        bool changed = ImGui::InputInt3(label.c_str(), ints);
        sol::table values = lua.create_table_with(1, ints[0], 2, ints[1], 3, ints[2]);
        return std::make_tuple(values, changed);
    };

    table["input_int_4"] = [&lua](const std::string& label, const sol::table& input_table) {
        int ints[4] = {input_table.get_or(1, 0), input_table.get_or(2, 0), input_table.get_or(3, 0),
                       input_table.get_or(4, 0)};
        bool changed = ImGui::InputInt4(label.c_str(), ints);
        sol::table values = lua.create_table_with(1, ints[0], 2, ints[1], 3, ints[2], 4, ints[3]);
        return std::make_tuple(values, changed);
    };

    table["input_float"] = [](const std::string& label, float value) {
        bool changed = ImGui::InputFloat(label.c_str(), &value);
        return std::make_tuple(value, changed);
    };

    table["input_float_2"] = [&lua](const std::string& label, const sol::table& input_table) {
        float floats[2] = {
            input_table.get_or(1, 0.0f),
            input_table.get_or(2, 0.0f),
        };
        bool changed = ImGui::InputFloat2(label.c_str(), floats);
        sol::table values = lua.create_table_with(1, floats[0], 2, floats[1]);
        return std::make_tuple(values, changed);
    };

    table["input_float_3"] = [&lua](const std::string& label, const sol::table& input_table) {
        float floats[3] = {input_table.get_or(1, 0.0f), input_table.get_or(2, 0.0f),
                           input_table.get_or(3, 0.0f)};
        bool changed = ImGui::InputFloat3(label.c_str(), floats);
        sol::table values = lua.create_table_with(1, floats[0], 2, floats[1], 3, floats[2]);
        return std::make_tuple(values, changed);
    };

    table["input_float_4"] = [&lua](const std::string& label, const sol::table& input_table) {
        float floats[4] = {input_table.get_or(1, 0.0f), input_table.get_or(2, 0.0f),
                           input_table.get_or(3, 0.0f), input_table.get_or(4, 0.0f)};
        bool changed = ImGui::InputFloat4(label.c_str(), floats);
        sol::table values =
            lua.create_table_with(1, floats[0], 2, floats[1], 3, floats[2], 4, floats[3]);
        return std::make_tuple(values, changed);
    };
}

void bind_input_drag(sol::table& table, sol::state_view& lua) {
    table["drag_int"] = sol::overload(
        [](const std::string& label, int value) {
            bool changed = ImGui::DragInt(label.c_str(), &value);
            return std::make_tuple(value, changed);
        },
        [](const std::string& label, int value, int speed) {
            bool changed = ImGui::DragInt(label.c_str(), &value, speed);
            return std::make_tuple(value, changed);
        },
        [](const std::string& label, int value, int speed, int min, int max) {
            bool changed = ImGui::DragInt(label.c_str(), &value, speed, min, max);
            return std::make_tuple(value, changed);
        });

    table["drag_float"] = [](const std::string& label, float value, float speed = 1, float min = 0,
                             float max = 0) {
        bool changed = ImGui::DragFloat(label.c_str(), &value, speed, min, max);
        return std::make_tuple(value, changed);
    };
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

    bind_popup(table);
    bind_menu(table);
    bind_tab(table);
    bind_tree(table);
    bind_table(table);

    bind_input(table, lua);
    bind_input_drag(table, lua);
    bind_input_slider(table, lua);
}
} // namespace lua::bindings::sledge
