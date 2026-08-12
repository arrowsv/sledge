#pragma once

#include "utils/os.hpp"

#include <filesystem>
#include <map>
#include <string>

namespace mods {
struct mod_state;
}

class config {
  public:
    static config& get() {
        static config instance;
        return instance;
    }

    void initialize(const std::filesystem::path& config_directory);
    bool save();

    std::filesystem::path game_directory;
    uint32_t fps_limit;
    bool skip_startup_videos;
    bool keep_launcher_open;
    utils::os::key open_key;
    std::map<std::string, mods::mod_state> mod_states;

  private:
    std::filesystem::path config_path = "sledge.json";
    void load_from_file(const std::filesystem::path& config_path);
};
