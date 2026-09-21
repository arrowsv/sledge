#include "config.hpp"
#include "utils/os.hpp"
#include "mods.hpp"

#include <filesystem>
#include <fstream>
#include <spdlog/spdlog.h>
#include <toml++/toml.hpp>

void config::initialize(const std::filesystem::path& config_directory) {
    config_path = config_directory / "sledge.toml";
    load_from_file();
}

void config::load_from_file() {
    toml::table tbl;

    if (std::filesystem::exists(config_path)) {
        try {
            tbl = toml::parse_file(config_path.string());
        } catch (const toml::parse_error& e) {
            spdlog::error("Failed to parse config file: {}", e.what());
        }
    }

    auto game_tbl = tbl["game"];
    game.skip_startup_videos = game_tbl["skip_startup_videos"].value_or(game.skip_startup_videos);

    auto sledge_tbl = tbl["sledge"];
    sledge.keep_launcher_open =
        sledge_tbl["keep_launcher_open"].value_or(sledge.keep_launcher_open);
    sledge.debug_logs_enabled =
        sledge_tbl["debug_logs_enabled"].value_or(sledge.debug_logs_enabled);
    sledge.imgui_demo_window = sledge_tbl["imgui_demo_window"].value_or(sledge.imgui_demo_window);

    std::string overlay_key_str =
        sledge_tbl["overlay_key"].value_or(utils::os::key_to_string(sledge.overlay_key));
    sledge.overlay_key = utils::os::key_from_string(overlay_key_str);

    if (auto mods_tbl = sledge_tbl["mods"].as_table()) {
        for (auto&& [id, value] : *mods_tbl) {
            if (auto state_tbl = value.as_table()) {
                mods::mod_state state;
                state.enabled = (*state_tbl)["enabled"].value_or(false);

                if (auto options = (*state_tbl)["options"].as_table()) {
                    for (auto&& [opt_key, opt_val] : *options) {
                        state.options[std::string(opt_key.str())] = opt_val.value_or("");
                    }
                }
                sledge.mod_states[std::string(id)] = state;
            }
        }
    }
}

void config::save() {
    toml::table tbl;

    toml::table game_tbl;
    game_tbl.insert("skip_startup_videos", game.skip_startup_videos);

    toml::table sledge_tbl;
    sledge_tbl.insert("keep_launcher_open", sledge.keep_launcher_open);
    sledge_tbl.insert("overlay_key", key_to_string(sledge.overlay_key));
    sledge_tbl.insert("debug_logs_enabled", sledge.debug_logs_enabled);
    sledge_tbl.insert("imgui_demo_window", sledge.imgui_demo_window);

    toml::table mods_tbl;
    for (const auto& [id, state] : sledge.mod_states) {
        toml::table state_tbl;
        state_tbl.insert("enabled", state.enabled);

        if (!state.options.empty()) {
            toml::table mod_options_tbl;
            for (const auto& [name, value] : state.options) {
                mod_options_tbl.insert(name, value);
            }
            state_tbl.insert("options", mod_options_tbl);
        }

        mods_tbl.insert(id, state_tbl);
    }

    if (!mods_tbl.empty()) {
        sledge_tbl.insert("mods", mods_tbl);
    }

    tbl.insert("game", game_tbl);
    tbl.insert("sledge", sledge_tbl);

    std::ofstream file(config_path);
    if (file.is_open()) {
        file << tbl;
        file.close();
    }
}
