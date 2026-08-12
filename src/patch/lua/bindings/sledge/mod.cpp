#include "mod.hpp"
#include "common/config.hpp"
#include "patch/gui/gui.hpp"
#include "patch/lua/manager.hpp"

#include <filesystem>
#include <plog/Log.h>
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
    mod_info["get_option"] = [&lua](const mods::mod_info& mod_info,
                                    const std::string& option_name) -> sol::optional<sol::object> {
        auto options_it = std::find_if(
            mod_info.options.begin(), mod_info.options.end(),
            [option_name](const mods::mod_option& o) { return o.name == option_name; });

        if (options_it == mod_info.options.end()) {
            PLOG_WARNING << "[" << mod_info.id << "] " << "Failed to find option '" << option_name
                         << "'.";
            return sol::nullopt;
        }

        const auto& states = config::get().mod_states;
        auto state_it = states.find(mod_info.id);
        if (state_it == states.end()) {
            PLOG_WARNING << "[" << mod_info.id << "] " << "Failed to find mod state.";
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

        PLOG_WARNING << "[" << mod_info.id << "] " << "Failed to find state for option '"
                     << option_name << "'.";
        return sol::nullopt;
    };
    mod_info["log"] = [](const mods::mod_info& mod_info, const std::string& message) {
        PLOG_INFO << "[" << mod_info.id << "] " << message;
    };
    mod_info["log_warn"] = [](const mods::mod_info& mod_info, const std::string& message) {
        PLOG_WARNING << "[" << mod_info.id << "] " << message;
    };
    mod_info["log_error"] = [](const mods::mod_info& mod_info, const std::string& message) {
        PLOG_ERROR << "[" << mod_info.id << "] " << message;
    };
    mod_info["register_window"] = [&lua](const mods::mod_info& mod_info, const std::string& title,
                                         sol::protected_function draw_func,
                                         sol::optional<sol::table> options) {
        sol::table options_table = options ? options.value() : lua.create_table();

        float width = options_table.get_or("width", 500.0f);
        float height = options_table.get_or("height", 300.0f);

        ImGuiWindowFlags flags = ImGuiWindowFlags_None;

        if (options_table.get_or("auto_resize", false))
            flags |= ImGuiWindowFlags_AlwaysAutoResize;

        if (options_table.get_or("no_resize", false))
            flags |= ImGuiWindowFlags_NoResize;

        if (options_table.get_or("no_decoration", false))
            flags |= ImGuiWindowFlags_NoDecoration;

        if (options_table.get_or("no_background", false))
            flags |= ImGuiWindowFlags_NoBackground;

        auto window = create_panel(title, mod_info, draw_func, flags, width, height);
        gui::manager::get().register_mod_window(window);
    };
    mod_info["register_overlay"] = [&lua](const mods::mod_info& mod_info, const std::string& title,
                                          sol::protected_function draw_func,
                                          sol::optional<sol::table> options) {
        sol::table options_table = options ? options.value() : lua.create_table();

        float width = options_table.get_or("width", 500.0f);
        float height = options_table.get_or("height", 300.0f);

        ImGuiWindowFlags flags = ImGuiWindowFlags_None;

        if (options_table.get_or("auto_resize", true))
            flags |= ImGuiWindowFlags_AlwaysAutoResize;

        if (options_table.get_or("no_resize", true))
            flags |= ImGuiWindowFlags_NoResize;

        if (options_table.get_or("no_decoration", true))
            flags |= ImGuiWindowFlags_NoDecoration;

        if (options_table.get_or("no_background", true))
            flags |= ImGuiWindowFlags_NoBackground;

        auto overlay = create_panel(title, mod_info, draw_func, flags, width, height);
        gui::manager::get().register_mod_overlay(overlay);
    };
    mod_info["register_event"] = [](const mods::mod_info& mod_info, lua::events::event event,
                                    sol::protected_function function,
                                    sol::optional<sol::table> options) {
        lua::events::event_callback callback;
        callback.mod_info = mod_info;
        callback.function = function;

        if (options.has_value()) {
            callback.filter = options.value().get_or<std::optional<std::string>>("filter", {});
            callback.id = options.value().get_or<std::string>("id", {});
        }

        lua::manager::get().register_event(event, callback);
    };
    mod_info["import"] = [lua](sol::this_environment te, const mods::mod_info& mod_info,
                               const std::string& module_name) {
        std::string relative = module_name;
        std::replace(relative.begin(), relative.end(), '.', '/');
        std::filesystem::path script_path =
            std::filesystem::path(mod_info.path) / (relative + ".lua");

        if (!std::filesystem::exists(script_path)) {
            throw sol::error("Module '" + module_name + "' not found at '" + script_path.string() +
                             "'");
        }

        sol::environment& env = te;
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
