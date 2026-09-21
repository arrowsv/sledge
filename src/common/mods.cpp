#include "mods.hpp"

#include "config.hpp"

#include <magic_enum.hpp>
#include <toml++/toml.hpp>
#include <spdlog/spdlog.h>

namespace mods {
    void manager::initialize(const std::filesystem::path& mods_directory) {
        m_discovered_mods = scan_mods_directory(mods_directory);
        sync_states_with_discovered();
    }

    void manager::sync_states_with_discovered() {
        std::map<std::string, mod_state> next_states;
        auto& current_states = config::get().sledge.mod_states;

        for (const auto& mod : m_discovered_mods) {
            auto [it, inserted] =
                next_states.try_emplace(mod.id, std::move(current_states[mod.id]));
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

    std::vector<mod_info>
    manager::scan_mods_directory(const std::filesystem::path& mods_directory) {
        std::vector<mod_info> list;
        if (!std::filesystem::exists(mods_directory))
            return list;

        for (const auto& entry : std::filesystem::directory_iterator(mods_directory)) {
            std::filesystem::path mod_config_path = entry.path() / "mod.toml";
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
                spdlog::warn("Skipped mod '{}': a mod already exists with the id '{}'.",
                             mod_config_path.string(), mod.value().id);
                continue;
            }
            list.push_back(mod.value());
        }
        return list;
    }

    std::optional<mod_info>
    manager::parse_mod_config(const std::filesystem::path& mod_config_path) {
        mod_info mod;
        try {
            toml::table tbl = toml::parse_file(mod_config_path.string());

            mod.id = tbl["id"].value_or("");
            if (mod.id.empty()) {
                spdlog::error("Skipped mod '{}': field 'id' is missing.", mod_config_path.string());
                return std::nullopt;
            }

            mod.name = tbl["name"].value_or("");
            if (mod.name.empty()) {
                spdlog::error("Skipped mod '{}': field 'name' is missing.",
                              mod_config_path.string());
                return std::nullopt;
            }

            mod.author = tbl["author"].value_or("N/A");
            mod.description = tbl["description"].value_or("");
            mod.version = tbl["version"].value_or("");

            if (auto options = tbl["options"].as_array()) {
                for (auto&& node : *options) {
                    auto& tbl = *node.as_table();

                    mod_option option;

                    std::string name = tbl["name"].value_or("");
                    if (name.empty()) {
                        spdlog::warn("Skipping option for mod '{}': field 'name' is missing.",
                                     mod.name);
                        continue;
                    }
                    option.name = name;

                    std::string type_str = tbl["type"].value_or("");
                    if (type_str.empty()) {
                        spdlog::warn("Skipping option '{}' for mod '{}': field 'type' is missing.",
                                     option.name, mod.name);
                        continue;
                    }

                    option.tooltip = tbl["tooltip"].value_or("");

                    auto type = magic_enum::enum_cast<mod_option_type>(type_str);
                    if (!type) {
                        spdlog::warn("Skipping option '{}' for mod '{}': '{}' is an invalid type.",
                                     option.name, mod.name, type_str);
                        continue;
                    }

                    switch (type.value()) {
                        case mod_option_type::custom: {
                            option.type = mod_option_type::custom;
                            option.choice_default = tbl["default"].value_or("");
                            break;
                        }
                        case mod_option_type::key: {
                            option.type = mod_option_type::key;
                            option.choice_default = tbl["default"].value_or("none");
                            break;
                        }
                        case mod_option_type::checkbox: {
                            option.type = mod_option_type::checkbox;
                            option.choice_default = tbl["default"].value_or("false");
                            break;
                        }
                        case mod_option_type::multiple: {
                            option.type = mod_option_type::multiple;
                            option.choice_default = tbl["default"].value_or("");

                            auto choices = tbl["choices"];
                            if (!choices) {
                                spdlog::warn("Skipping option '{}' for mod '{}': field 'choices' "
                                             "is missing.",
                                             option.name, mod.name);
                                continue;
                            }

                            if (auto choices_arr = choices.as_array()) {
                                if (choices_arr->empty()) {
                                    spdlog::warn("Skipping option '{}' for mod '{}': 'choices' "
                                                 "array is empty.",
                                                 option.name, mod.name);
                                    continue;
                                }

                                if (option.choice_default.empty()) {
                                    auto choice_first = (*choices_arr).get(0);
                                    if (!choice_first || !choice_first->is_string()) {
                                        spdlog::warn("Skipping option '{}' for mod '{}': first "
                                                     "choice is invalid or a non-string value.",
                                                     option.name, mod.name);
                                        continue;
                                    }

                                    option.choice_default = choice_first->as_string()->get();
                                }

                                for (auto&& choice_val : *choices_arr) {
                                    auto choice_str = choice_val.as_string();
                                    if (!choice_str) {
                                        spdlog::warn("Skipping choice of option '{}' for mod '{}': "
                                                     "choice is a non-string value.",
                                                     option.name, mod.name);
                                        continue;
                                    } else if (choice_str->get().empty()) {
                                        spdlog::warn("Skipping choice of option '{}' for mod '{}': "
                                                     "choice is empty.",
                                                     option.name, mod.name);
                                        continue;
                                    }

                                    option.choice_multiple.push_back(choice_str->get());
                                }
                            } else if (auto choices_str = choices.as_string()) {
                                if (choices_str->get().empty()) {
                                    spdlog::warn("Skipping option '{}' for mod '{}': 'choices' "
                                                 "string is empty.",
                                                 option.name, mod.name);
                                    continue;
                                }

                                auto options_it =
                                    std::find_if(mod.options.begin(), mod.options.end(),
                                                 [choices_str](const mod_option& o) {
                                                     return o.name == choices_str->get();
                                                 });

                                if (options_it == mod.options.end()) {
                                    spdlog::warn("Skipping option '{}' for mod '{}': option '{}' "
                                                 "does not exist.",
                                                 option.name, mod.name, choices_str->get());
                                    continue;
                                }

                                option.choice_multiple = options_it->choice_multiple;

                                if (option.tooltip.empty() && !options_it->tooltip.empty()) {
                                    option.tooltip = options_it->tooltip;
                                }

                                if (option.choice_default.empty() &&
                                    !option.choice_multiple.empty()) {
                                    option.choice_default = options_it->choice_default;
                                }
                            } else {
                                spdlog::warn("Skipping option '{}' for mod '{}': field 'choices' "
                                             "must be an array or string.",
                                             option.name, mod.name);
                                continue;
                            }
                            break;
                        }
                    }
                    mod.options.push_back(option);
                }
            }
        } catch (const toml::parse_error& e) {
            spdlog::error("Failed parsing mod '{}': {}", mod_config_path.string(), e.what());
            return std::nullopt;
        }
        return mod;
    }

    std::vector<mod_info> manager::get_enabled_mods() {
        std::vector<mod_info> enabled_mods;
        auto& states = config::get().sledge.mod_states;

        for (const auto& mod : m_discovered_mods) {
            if (states.contains(mod.id) && states[mod.id].enabled) {
                enabled_mods.push_back(mod);
            }
        }
        return enabled_mods;
    }

    const std::vector<mod_info>& manager::get_discovered_mods() { return m_discovered_mods; }
}
