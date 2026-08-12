#pragma once

#include "events/events.hpp"

#include <filesystem>
#include <mutex>
#include <plog/Log.h>
#include <sol/forward.hpp>

namespace lua {
class manager {
  public:
    static manager& get() {
        static manager instance;
        return instance;
    }

    void initialize();
    void reload_mods();
    void run_enabled_mods();
    bool is_loading();

    sol::protected_function_result execute_script_file(const std::filesystem::path& script_path,
                                                       sol::environment& env);
    sol::protected_function_result execute_script_string(const std::string& script);
    sol::protected_function_result execute_function(sol::protected_function& func);
    sol::protected_function_result execute_function_with_context(sol::protected_function& func,
                                                                 sol::table& context);

    void trigger_event(lua::events::event event, const lua::events::event_context& context,
                       std::optional<std::string_view> filter);
    void register_event(lua::events::event event, events::event_callback callback);
    bool has_event_subscriber(lua::events::event event, std::string_view filter_name);

  private:
    bool m_loading = false;
    std::recursive_mutex m_lua_state_mutex;
    std::unique_ptr<sol::state> m_lua_state = nullptr;
    std::map<lua::events::event, std::vector<lua::events::event_callback>> m_event_registry;
};

} // namespace lua
