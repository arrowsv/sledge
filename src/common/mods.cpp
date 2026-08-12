#include "mods.hpp"
#include "config.hpp"

#include <fstream>
#include <nlohmann/json.hpp>
#include <plog/Log.h>

namespace mods {
void manager::initialize(const std::filesystem::path& mods_directory) {
    m_discovered_mods = scan_mods_directory(mods_directory);
    sync_states_with_discovered();
}

void manager::sync_states_with_discovered() {
    std::map<std::string, mod_state> next_states;
    auto& current_states = config::get().mod_states;

    for (const auto& mod : m_discovered_mods) {
        auto [it, inserted] = next_states.try_emplace(mod.id, std::move(current_states[mod.id]));
        auto& state = it->second;

        std::map<std::string, std::string> active_options;

        for (const auto& opt : mod.options) {
            auto& current_selection = state.options[opt.name];

            switch (opt.type) {
            case mods::mod_option_type::custom:
            case mods::mod_option_type::key:
            case mods::mod_option_type::checkbox: {
                if (current_selection.empty()) {
                    current_selection = opt.choice_default;
                }
                break;
            }
            case mods::mod_option_type::multiple: {
                // Reset to default if it doesn't exist in the defined choices.
                if (std::find(opt.choice_multiple.begin(), opt.choice_multiple.end(),
                              current_selection) == opt.choice_multiple.end())
                    current_selection = opt.choice_default;
            } break;
            }

            active_options[opt.name] = current_selection;
        }
        state.options = std::move(active_options);
    }
    current_states = std::move(next_states);
}

std::vector<mod_info> manager::scan_mods_directory(const std::filesystem::path& mods_directory) {
    std::vector<mod_info> list;
    if (!std::filesystem::exists(mods_directory))
        return list;

    for (const auto& entry : std::filesystem::directory_iterator(mods_directory)) {
        std::filesystem::path mod_config_path = entry.path() / "mod.json";
        if (!std::filesystem::exists(mod_config_path))
            continue;

        std::optional<mod_info> mod = parse_mod_config(mod_config_path);
        if (!mod.has_value())
            continue;

        mod.value().path = entry.path().string();

        auto exists = std::ranges::find_if(
            list, [&](const std::string& existing_id) { return existing_id == mod.value().id; },
            &mod_info::id);

        if (exists != list.end()) {
            PLOG_WARNING << "Skipped mod located at '" << mod_config_path
                         << "'. A mod already exists with the id '" << mod.value().id << "'.";
            continue;
        }
        list.push_back(mod.value());
    }
    return list;
}

std::optional<mod_info> manager::parse_mod_config(const std::filesystem::path& mod_config_path) {
    mod_info mod;
    try {
        std::ifstream f(mod_config_path);
        const auto data = nlohmann::ordered_json::parse(f);

        mod.id = data.value("id", "");
        mod.name = data.value("name", "");
        mod.author = data.value("author", "Unknown");
        mod.description = data.value("description", "");
        mod.version = data.value("version", "");

        if (mod.id.empty()) {
            PLOG_WARNING << "Skipped mod located at '" << mod_config_path
                         << "'. The 'id' field is required.";
            return {};
        }

        if (mod.name.empty())
            mod.name = mod_config_path.parent_path().filename().string();

        if (data.contains("options") && data["options"].is_object()) {
            for (const auto& [name, values] : data["options"].items()) {
                if (name.empty())
                    continue;

                mod_option option;
                option.name = name;

                auto type = values.value("type", "");
                if (type == "custom") {
                    option.type = mod_option_type::custom;
                    option.choice_default = values.value("default", "");
                } else if (type == "key") {
                    option.type = mod_option_type::key;
                    option.choice_default = values.value("default", "none");
                } else if (type == "checkbox") {
                    option.type = mod_option_type::checkbox;
                    option.choice_default = values.value("default", "false");
                } else if (type == "multiple") {
                    option.type = mod_option_type::multiple;
                    option.choice_default = values.value("default", "");

                    auto choices_it = values.find("choices");
                    if (choices_it == values.end()) {
                        PLOG_WARNING << "[" << mod.name << "] Option '" << option.name
                                     << "' is missing 'choices'.";
                        continue;
                    }

                    // Check if option has its own choices or wants to copy another option's.
                    if (choices_it->is_array()) {
                        const auto& choices_array = *choices_it;
                        if (option.choice_default.empty() && !choices_array.empty()) {
                            option.choice_default = choices_array[0].get<std::string>();
                        }

                        for (const auto& value : choices_array) {
                            if (value.is_string()) {
                                option.choice_multiple.push_back(value.get<std::string>());
                            }
                        }
                    } else if (choices_it->is_string()) {
                        std::string option_to_copy = choices_it->get<std::string>();
                        auto options_it = std::find_if(mod.options.begin(), mod.options.end(),
                                                       [option_to_copy](const mod_option& o) {
                                                           return o.name == option_to_copy;
                                                       });

                        if (options_it == mod.options.end()) {
                            PLOG_WARNING << "[" << mod.name << "] Option '" << option.name
                                         << "' attempted to copy non-existing option '"
                                         << option_to_copy << "'.";
                            continue;
                        }

                        option.choice_multiple = options_it->choice_multiple;

                        if (option.choice_default.empty() && !option.choice_multiple.empty()) {
                            option.choice_default = option.choice_multiple[0];
                        }
                    }
                } else {
                    PLOG_WARNING << "[" << mod.name << "] Option '" << option.name
                                 << "' requires a valid type. Available types: 'custom', 'key', or "
                                    "'multiple'.";
                    continue;
                }
                mod.options.push_back(option);
            }
        }
    } catch (const nlohmann::json::exception& e) {
        PLOG_ERROR << "Failed parsing mod config file located at '" << mod_config_path
                   << "'. Error: " << e.what();
        return {};
    }
    return mod;
}

std::vector<mod_info> manager::get_enabled_mods() {
    std::vector<mod_info> enabled_mods;
    auto& states = config::get().mod_states;

    for (const auto& mod : m_discovered_mods) {
        if (states.contains(mod.id) && states[mod.id].enabled) {
            enabled_mods.push_back(mod);
        }
    }
    return enabled_mods;
}

const std::vector<mod_info>& manager::get_discovered_mods() { return m_discovered_mods; }
} // namespace mods
