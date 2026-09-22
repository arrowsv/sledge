#include "mod.hpp"
#include "common/config.hpp"
#include "patch/lua/manager.hpp"

#include <filesystem>
#include <spdlog/spdlog.h>
#include <imgui.h>
#include <sol/sol.hpp>

namespace lua::bindings::sledge {

    void bind_mod(sol::state_view& lua) {
        auto types = lua["types"].get_or_create<sol::table>();

        auto mod_info = types.new_usertype<mods::mod_info>("mod_info");
        mod_info["id"] = sol::readonly(&mods::mod_info::id);

        mod_info["name"] = sol::readonly(&mods::mod_info::name);

        mod_info["options"] = sol::readonly_property([&lua](mods::mod_info& self) {
            sol::table options_table = lua.create_table();

            const auto& states = config::get().sledge.mod_states;
            auto state_it = states.find(self.id);
            if (state_it == states.end()) {
                spdlog::error("Failed to find state for mod '{}'.", self.id);
                return options_table;
            }

            for (const auto& option : self.options) {
                const auto& option_states = state_it->second.options;
                auto opt_it = option_states.find(option.name);
                if (opt_it == option_states.end()) {
                    spdlog::error("Failed to find state of option '{}' for mod '{}'.", option.name,
                                  self.id);
                    continue;
                }

                const std::string& option_value = opt_it->second;

                switch (option.type) {
                    case mods::mod_option_type::key:
                        options_table[option.name] =
                            sol::make_object(lua, utils::os::key_from_string(option_value));
                        break;

                    case mods::mod_option_type::checkbox:
                        options_table[option.name] = sol::make_object(lua, option_value == "true");
                        break;

                    case mods::mod_option_type::multiple:
                    case mods::mod_option_type::custom:
                        options_table[option.name] = sol::make_object(lua, option_value);
                        break;

                    default:
                        spdlog::warn("Unknown option type for option '{}'.", option.name);
                        break;
                }
            }

            return options_table;
        });

        mod_info["import"] = [lua](sol::this_environment this_env, const mods::mod_info& mod_info,
                                   const std::string& module_name) {
            std::string relative = module_name;
            std::replace(relative.begin(), relative.end(), '.', '/');
            std::filesystem::path script_path =
                std::filesystem::path(mod_info.path) / (relative + ".lua");

            if (!std::filesystem::exists(script_path)) {
                throw sol::error("Module '" + module_name + "' not found at '" +
                                 script_path.string() + "'");
            }

            sol::environment& env = this_env;
            auto result = lua::manager::get().execute_script_file(script_path.string(), env);
            if (!result.valid()) {
                sol::error err = result;
                throw sol::error("Error loading module '" + module_name + "': " + err.what());
            }

            return result;
        };
    }

    void bind_mod_environment(sol::state_view& lua, sol::environment& environment,
                              const mods::mod_info& mod_info) {
        environment["mod"] = mod_info;
    }
}
