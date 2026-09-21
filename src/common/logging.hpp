#pragma once

#include <filesystem>

namespace logging {
    void initialize(const std::filesystem::path& log_directory,
                                                std::string_view log_file_name);
    void update_level();
}