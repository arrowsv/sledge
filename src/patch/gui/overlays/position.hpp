#pragma once

#include "patch/gui/gui.hpp"

class position_overlay : public gui::panel {
  public:
    position_overlay()
        : panel("Position", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground |
                                ImGuiWindowFlags_AlwaysAutoResize) {}
    void draw() override;
};