#include "mod.hpp"
#include "common/config.hpp"
#include "patch/gui/gui.hpp"
#include "patch/lua/manager.hpp"

#include <filesystem>
#include <spdlog/spdlog.h>
#include <imgui.h>
#include <sol/sol.hpp>

namespace lua::bindings::sledge {

std::shared_ptr<gui::mod_panel> create_panel(std::string title, const mods::mod_info mod_info,
                                             sol::protected_function& draw_function,
                                             ImGuiWindowFlags flags, float width, float height) {
    return std::make_shared<gui::mod_panel>(title, mod_info, draw_function, flags,
                                            ImVec2{width, height});
}

    void bind_mod(sol::state_view& lua) {
        auto types = lua["types"].get_or_create<sol::table>();

        auto mod_info = types.new_usertype<mods::mod_info>("mod_info");
        mod_info["id"] = sol::readonly(&mods::mod_info::id);
        mod_info["name"] = sol::readonly(&mods::mod_info::name);
        mod_info["version"] = sol::readonly(&mods::mod_info::version);
        mod_info["description"] = sol::readonly(&mods::mod_info::description);
        mod_info["author"] = sol::readonly(&mods::mod_info::author);
        mod_info["path"] = sol::readonly(&mods::mod_info::path);
        mod_info["get_option"] =
            [&lua](const mods::mod_info& mod_info,
                   const std::string& option_name) -> sol::optional<sol::object> {
            auto options_it = std::find_if(
                mod_info.options.begin(), mod_info.options.end(),
                [option_name](const mods::mod_option& o) { return o.name == option_name; });

            if (options_it == mod_info.options.end()) {
                spdlog::error("Failed to find option '{}' for mod '{}'.", option_name, mod_info.id);
                return sol::nullopt;
            }

            const auto& states = config::get().mod_states;
            auto state_it = states.find(mod_info.id);
            if (state_it == states.end()) {
                spdlog::error("Failed to find state for mod '{}'.", option_name, mod_info.id);
                return sol::nullopt;
            }

            std::string option_value;

            const auto& option_states = state_it->second.options;
            auto opt_it = option_states.find(option_name);
            if (opt_it != option_states.end()) {
                option_value = opt_it->second;
            }

            switch (options_it->type) {
                case mods::mod_option_type::key:
                    return sol::make_object(lua, utils::os::key_from_string(option_value));

                case mods::mod_option_type::checkbox:
                    return sol::make_object(lua, option_value == "true");

                case mods::mod_option_type::multiple:
                case mods::mod_option_type::custom:
                    return sol::make_object(lua, option_value);
            }

            spdlog::error("Failed to find state of option '{}' for mod '{}'.", option_name,
                          mod_info.id);
            return sol::nullopt;
        };
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
} // namespace lua::bindings::sledge
