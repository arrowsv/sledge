#include "utils.hpp"
#include "common/mods.hpp"

#include <sol/sol.hpp>

namespace lua::api::utils {
    template <typename T> sol::table create_table(sol::state_view& lua, T list, int count) {
        sol::table t = lua.create_table(count, 0);

        for (int32_t i = 0; i < count; ++i) {
            t[i + 1] = &list[i];
        }

        return t;
    }

    sol::optional<mods::mod_info> get_env_mod(sol::this_environment this_env) {
        sol::environment& env = this_env;

        if (!env)
            return {};

        return env["mod"];
    }

}
