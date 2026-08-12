#include "fps.hpp"

#include "patch/rfg/game.hpp"
#include <imgui.h>

void fps_overlay::draw() { ImGui::Text("FPS: %f", *rfg::g_frames_per_second()); }
