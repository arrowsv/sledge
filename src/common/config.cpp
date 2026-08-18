#include "config.hpp"
#include "mods.hpp"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
#include <plog/Log.h>

void config::initialize(const std::filesystem::path& config_directory) {
    config_path = config_directory / "sledge.json";
    load_from_file(config_path);
}

void config::load_from_file(const std::filesystem::path& config_file) {
    nlohmann::ordered_json data = nlohmann::json::object();

    if (std::filesystem::exists(config_file)) {
        std::ifstream file(config_path);
        if (file.is_open()) {
            try {
                data = nlohmann::json::parse(file);
            } catch (const nlohmann::json::exception&) {
                PLOG_ERROR << "Malformed JSON file. Using defaults.";
            }
        } else {
            PLOG_ERROR << "Config file could not be opened. Using defaults.";
        }
    }

    fps_limit = data.value("fps_limit", 120);
    skip_startup_videos = data.value("skip_startup_videos", true);

    auto open_key_string = data.value("open_key", "f1");
    open_key = utils::os::key_from_string(open_key_string);

    if (data.contains("mod_states") && data["mod_states"].is_object()) {
        for (const auto& [id, value] : data["mod_states"].items()) {
            mods::mod_state state;
            state.enabled = value.value("enabled", false);
            if (value.contains("options") && value["options"].is_object()) {
                for (const auto& [option_key, option_value] : value["options"].items()) {
                    if (option_value.is_string()) {
                        state.options[option_key] = option_value.get<std::string>();
                    }
                }
            }
            mod_states[id] = state;
        }
    }
}

bool config::save() {
    nlohmann::ordered_json data = {{"fps_limit", fps_limit},
                                   {"skip_startup_videos", skip_startup_videos},
                                   {"open_key", key_to_string(open_key)}};

    for (const auto& [id, state] : mod_states) {
        nlohmann::ordered_json mod_entry;
        mod_entry["enabled"] = state.enabled;
        if (!state.options.empty()) {
            nlohmann::ordered_json options_table = nlohmann::json::object();

            for (const auto& [k, v] : state.options)
                options_table[k] = v;

            mod_entry["options"] = options_table;
        }
        data["mod_states"][id] = mod_entry;
    }

    std::ofstream file(config_path);
    if (file.is_open()) {
        file << std::setw(4) << data;
        return true;
    }
    return false;
}
