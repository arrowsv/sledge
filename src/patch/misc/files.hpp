#pragma once

#include <sol/forward.hpp>
#include <filesystem>

namespace misc::files {
    void register_file(const std::filesystem::path& file_path);
    void register_packfile(const std::filesystem::path& file_path);
    void register_xml_edit(const std::string& file_name, sol::protected_function modify_function);
    void apply_patches();
}