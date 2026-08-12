#include "file_viewer.hpp"

#include <imgui.h>

void file_viewer_window::draw() {
    float total_width = ImGui::GetContentRegionAvail().x;
    float total_height = ImGui::GetContentRegionAvail().y;

    float item_spacing_x = ImGui::GetStyle().ItemSpacing.x;
    float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;

    float button_height = ImGui::GetFrameHeight();

    float bottom_section_height = item_spacing_y + item_spacing_y + button_height;
    float child_height = total_height - bottom_section_height;

    float file_list_width = 180;
    float file_info_width = total_width - file_list_width - item_spacing_x;

    if (ImGui::BeginChild("file_list", {file_list_width, child_height}, ImGuiChildFlags_Borders,
                          ImGuiWindowFlags_HorizontalScrollbar)) {
    }
    ImGui::EndChild();
    ImGui::SameLine();
    if (ImGui::BeginChild("file_info", {file_info_width, child_height}, ImGuiChildFlags_Borders,
                          ImGuiWindowFlags_HorizontalScrollbar)) {
    }
    ImGui::EndChild();
}
