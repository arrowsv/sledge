#include "position.hpp"

#include "common/utils/imgui.hpp"
#include "patch/rfg/player.hpp"
#include <imgui.h>
#include <string>

void position_widget::draw() {
    auto player = rfg::get_local_player();

    float x = player ? player->position.x : 0.0;
    float y = player ? player->position.y : 0.0;
    float z = player ? player->position.z : 0.0;

    if (utils::imgui::begin_property_table("sledge_position")) {
        utils::imgui::begin_property_row("X");
        ImGui::TextUnformatted(std::to_string(x).c_str());
        utils::imgui::end_property_row();

        utils::imgui::begin_property_row("Y");
        ImGui::TextUnformatted(std::to_string(y).c_str());
        utils::imgui::end_property_row();

        utils::imgui::begin_property_row("Z");
        ImGui::TextUnformatted(std::to_string(z).c_str());
        utils::imgui::end_property_row();

        utils::imgui::end_property_table();
    }
}
