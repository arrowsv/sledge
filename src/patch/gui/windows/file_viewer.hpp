#pragma once

#include "patch/gui/gui.hpp"

class file_viewer_window : public gui::panel {
  public:
    file_viewer_window() : panel("File viewer") {}
    void draw() override;
};
