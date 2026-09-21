#pragma once

#include "patch/gui/manager.hpp"

class fps_widget : public gui::panel {
  public:
    fps_widget()
        : panel("FPS") {}
    void draw() override;
};