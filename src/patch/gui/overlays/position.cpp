#include "position.hpp"

#include "patch/rfg/player.hpp"
#include <imgui.h>

void position_overlay::draw() {
    auto player = rfg::get_local_player();
    if (!player)
        return;
    ImGui::Text("X: %f", player->position.x);
    ImGui::Text("Y: %f", player->position.y);
    ImGui::Text("Z: %f", player->position.z);
}
