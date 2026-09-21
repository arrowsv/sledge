#pragma once

#include "patch/gui/manager.hpp"

class position_widget : public gui::panel {
  public:
    position_widget()
        : panel("Position") {}
    void draw() override;
};