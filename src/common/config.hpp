#pragma once

#include "mods.hpp"
#include "utils/os.hpp"

#include <filesystem>
#include <map>
#include <string>

struct game_config {
    bool skip_startup_videos = true;
};

struct sledge_config {
    std::map<std::string, mods::mod_state> mod_states = {};
    bool keep_launcher_open = true;
    utils::os::key overlay_key = utils::os::key::f1;
    bool debug_logs_enabled = false;
    bool imgui_demo_window = false;
};

class config {
  public:
    static config& get() {
        static config instance;
        return instance;
    }

    void initialize(const std::filesystem::path& config_directory);
    void save();

    game_config game;
    sledge_config sledge;

  private:
    std::filesystem::path config_path;
    void load_from_file();
};
