#include "manager.hpp"

#include "bindings/core.hpp"
#include "common/mods.hpp"
#include "magic_enum.hpp"
#include "patch/gui/gui.hpp"
#include "patch/lua/bindings/sledge/mod.hpp"
#include "patch/lua/events/events.hpp"
#include "patch/rfg/game.hpp"
#include "sol/state_handling.hpp"

#include <mutex>
#include <plog/Log.h>
#include <sol/sol.hpp>

namespace lua {
bool manager::is_loading() { return m_loading; }

void manager::initialize() {
    std::lock_guard<std::recursive_mutex> lock(m_lua_state_mutex);
    m_loading = true;

    m_lua_state = std::make_unique<sol::state>();
    m_lua_state->open_libraries(sol::lib::base, sol::lib::table, sol::lib::string, sol::lib::math);

    lua::bindings::bind_all(*m_lua_state);
    run_enabled_mods();
    m_loading = false;
}

void manager::reload_mods() {
    std::lock_guard<std::recursive_mutex> lock(m_lua_state_mutex);
    m_loading = true;

    gui::manager::get().clear_mod_panels();
    m_event_registry.clear();
    m_lua_state->collect_garbage();

    run_enabled_mods();
    m_loading = false;
    PLOG_INFO << "Reloaded mods.";
}

void manager::run_enabled_mods() {
    std::lock_guard<std::recursive_mutex> lock(m_lua_state_mutex);
    if (!m_lua_state)
        return;

    auto enabled_mods = mods::manager::get().get_enabled_mods();
    for (const auto& mod : enabled_mods) {
        sol::environment environment(*m_lua_state, sol::create, m_lua_state->globals());
        std::filesystem::path script_path = std::filesystem::path(mod.path) / "mod.lua";

        bindings::sledge::bind_mod_environment(*m_lua_state, environment, mod);

        auto result = execute_script_file(script_path, environment);
        if (!result.valid()) {
            sol::error err = result;
            PLOG_ERROR << "[" << mod.name << "] Failed to run script located at '"
                       << script_path.string() << "': " << err.what();
        }
    }

    PLOG_DEBUG << "Finished running enabled mods.";
}

sol::protected_function_result
manager::execute_script_file(const std::filesystem::path& script_path, sol::environment& env) {
    std::lock_guard<std::recursive_mutex> lock(m_lua_state_mutex);
    if (m_lua_state == nullptr) {
        PLOG_ERROR << "Tried executing Lua before initializing.";
        return sol::protected_function_result();
    }
    return m_lua_state->safe_script_file(script_path.string(), env, sol::script_pass_on_error);
}

sol::protected_function_result manager::execute_script_string(const std::string& script) {
    std::lock_guard<std::recursive_mutex> lock(m_lua_state_mutex);
    if (m_lua_state == nullptr) {
        PLOG_ERROR << "Tried executing Lua before initializing.";
        return sol::protected_function_result();
    }
    return m_lua_state->safe_script(script, sol::script_pass_on_error);
}

sol::protected_function_result manager::execute_function(sol::protected_function& func) {
    std::lock_guard<std::recursive_mutex> lock(m_lua_state_mutex);
    if (m_lua_state == nullptr || !func.valid()) {
        PLOG_ERROR << "Tried executing Lua before initializing or function was invalid.";
        return sol::protected_function_result();
    }
    return func();
}

sol::protected_function_result manager::execute_function_with_context(sol::protected_function& func,
                                                                      sol::table& context) {
    std::lock_guard<std::recursive_mutex> lock(m_lua_state_mutex);
    if (m_lua_state == nullptr || !func.valid()) {
        PLOG_ERROR << "Tried executing Lua before initializing or function was invalid.";
        return sol::protected_function_result();
    }
    return func(context);
}

void manager::trigger_event(lua::events::event event, const lua::events::event_context& context,
                            std::optional<std::string_view> filter) {
    if (m_loading || *rfg::g_multiplayer())
        return;

    std::lock_guard<std::recursive_mutex> lock(m_lua_state_mutex);
    if (!m_lua_state)
        return;

    auto subscribers = m_event_registry.find(event);
    if (subscribers == m_event_registry.end())
        return;

    sol::state_view lua(*m_lua_state);
    sol::table context_table = context.to_table(lua);

    for (auto& callback : subscribers->second) {
        if (filter.has_value() && callback.filter.has_value())
            if (filter.value() != callback.filter.value())
                continue;

        auto result = execute_function_with_context(callback.function, context_table);
        if (!result.valid()) {
            sol::error err = result;
            PLOG_ERROR << "Failed to run event function: " << err.what();
        }
    }
}

void manager::register_event(lua::events::event event, lua::events::event_callback callback) {
    std::lock_guard<std::recursive_mutex> lock(m_lua_state_mutex);
    m_event_registry[event].push_back(callback);
}

bool manager::has_event_subscriber(lua::events::event event, std::string_view filter_name) {
    std::lock_guard<std::recursive_mutex> lock(m_lua_state_mutex);

    auto subscribers = m_event_registry.find(event);
    if (subscribers == m_event_registry.end())
        return false;

    for (const auto& callback : subscribers->second) {
        if (!callback.filter.has_value() || callback.filter.value() == filter_name) {
            PLOG_DEBUG << "Event " << magic_enum::enum_name(event) << " has subscriber for "
                       << filter_name << ".";
            return true;
        }
    }
    return false;
}

} // namespace lua
