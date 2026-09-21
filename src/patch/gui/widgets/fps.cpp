#include "fps.hpp"

#include "common/utils/imgui.hpp"
#include "patch/rfg/game.hpp"

#include <imgui.h>

void fps_widget::draw() {
    if (utils::imgui::begin_property_table("sledge_fps")) {
        utils::imgui::begin_property_row("FPS");
        ImGui::TextUnformatted(std::to_string(*rfg::g_frames_per_second()).c_str());
        utils::imgui::end_property_row();
        utils::imgui::end_property_table();
    }
}
