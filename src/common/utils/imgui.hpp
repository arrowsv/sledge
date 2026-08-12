#pragma once

#include "os.hpp"

namespace utils::imgui {
void initialize_styles();
void initialize_fonts();
bool key_combobox(const char* label, os::key* current_key);
void set_help_marker(const std::string& text);
bool begin_help_marker();
void end_help_marker();

} // namespace utils::imgui
