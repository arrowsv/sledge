#pragma once

#include "os.hpp"

namespace utils::imgui {
    void initialize();
    void initialize_styles();
    void initialize_fonts();

    bool key_combobox(const char* label, os::key* current_key);

    bool begin_tooltip();
    void set_tooltip(const std::string& text);
    void end_tooltip();

    void set_help_marker(const std::string& text);
    bool begin_help_marker();
    void end_help_marker();

    bool begin_property_table(const char* str_id);
    void end_property_table();
    void begin_property_row(const char* label);
    void end_property_row();
    bool in_property_table();
}
