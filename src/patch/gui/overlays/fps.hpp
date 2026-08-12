#pragma once

#include "patch/gui/gui.hpp"

class fps_overlay : public gui::panel {
  public:
    fps_overlay()
        : panel("FPS", ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground |
                           ImGuiWindowFlags_AlwaysAutoResize) {}
    void draw() override;
};