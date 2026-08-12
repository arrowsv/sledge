#include "utils.hpp"

#include <sol/sol.hpp>

namespace lua::api::utils {
template <typename T> sol::table create_table(sol::state_view& lua, T list, int count) {
    sol::table t = lua.create_table(count, 0);

    for (int32_t i = 0; i < count; ++i) {
        t[i + 1] = &list[i];
    }

    return t;
}
} // namespace lua::api::utils
