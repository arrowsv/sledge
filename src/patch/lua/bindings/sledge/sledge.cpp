#include "sledge.hpp"

#include "common/mods.hpp"
#include "common/utils/os.hpp"
#include "patch/gui/manager.hpp"
#include "patch/lua/bindings/utils.hpp"
#include "patch/lua/manager.hpp"
#include "patch/main.hpp"
#include "patch/misc/files.hpp"

#include <spdlog/spdlog.h>
#include <imgui.h>
#include <sol/sol.hpp>

namespace lua::bindings::sledge {

    std::shared_ptr<gui::panel> create_panel(std::string title,
                                             sol::optional<mods::mod_info> mod_info,
                                             sol::protected_function draw_function,
                                             ImGuiWindowFlags flags, float width, float height) {
        if (mod_info) {
            return std::make_shared<gui::panel>(title, mod_info.value(), std::move(draw_function),
                                                flags, ImVec2{width, height});
        } else {
            return std::make_shared<gui::panel>(title, std::move(draw_function), flags,
                                                ImVec2{width, height});
        }
    }

    void bind_sledge(sol::state_view& lua) {
        auto sledge = lua["sledge"].get_or_create<sol::table>();

        sledge["register_file"] = [](sol::this_environment this_env, const std::string& file_path) {
            auto mod_info = api::utils::get_env_mod(this_env);
            std::filesystem::path base_path =
                mod_info ? std::filesystem::path(mod_info->path)
                         : utils::os::get_module_directory(g_sledge_module_base);
            misc::files::register_file(base_path / file_path);
        };

        sledge["register_packfile"] = [](sol::this_environment this_env,
                                         const std::string& file_path) {
            auto mod_info = api::utils::get_env_mod(this_env);
            std::filesystem::path base_path =
                mod_info ? std::filesystem::path(mod_info->path)
                         : utils::os::get_module_directory(g_sledge_module_base);
            misc::files::register_packfile(base_path / file_path);
        };

        sledge["register_xml_edit"] = [](const std::string& file_name,
                                         sol::protected_function function) {
            misc::files::register_xml_edit(file_name, function);
        };

        sledge["log"] = [](sol::this_environment this_env, const std::string& message) {
            auto mod_info = api::utils::get_env_mod(this_env);
            if (mod_info) {
                spdlog::info("[{}] {}", mod_info->id, message);
            } else {
                spdlog::info(message);
            }
        };

        sledge["log_warn"] = [](sol::this_environment this_env, const std::string& message) {
            auto mod_info = api::utils::get_env_mod(this_env);
            if (mod_info) {
                spdlog::warn("[{}] {}", mod_info->id, message);
            } else {
                spdlog::warn(message);
            }
        };

        sledge["log_error"] = [](sol::this_environment this_env, const std::string& message) {
            auto mod_info = api::utils::get_env_mod(this_env);
            if (mod_info) {
                spdlog::error("[{}] {}", mod_info->id, message);
            } else {
                spdlog::error(message);
            }
        };

        sledge["register_window"] = [&lua](sol::this_environment this_env, const std::string& title,
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

            auto mod_info = api::utils::get_env_mod(this_env);

            auto window = create_panel(title, mod_info, draw_func, flags, width, height);
            gui::manager::get().register_window(window);
        };

        sledge["register_widget"] = [&lua](sol::this_environment this_env, const std::string& title,
                                           sol::protected_function draw_func) {
            auto mod_info = api::utils::get_env_mod(this_env);
            auto widget =
                create_panel(title, mod_info, draw_func, ImGuiWindowFlags_None, 500.0f, 300.0f);
            gui::manager::get().register_widget(widget);
        };

        sledge["register_event"] = [](sol::this_environment this_env, lua::events::event event,
                                      sol::protected_function function,
                                      sol::optional<sol::table> options) {
            lua::events::event_callback callback;

            auto mod_info = api::utils::get_env_mod(this_env);
            if (mod_info) {
                callback.mod_info = mod_info.value();
            }
            callback.function = function;

            if (options.has_value()) {
                callback.filter = options.value().get_or<std::optional<std::string>>("filter", {});
                callback.id = options.value().get_or<std::string>("id", {});
            }

            lua::manager::get().register_event(event, callback);
        };
    }
}
