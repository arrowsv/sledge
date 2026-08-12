#include "patch/rfg/math/matrix.hpp"

#include <sol/sol.hpp>

namespace lua::bindings::rfg {
void bind_matrix(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();
    auto matrix = types.new_usertype<::rfg::matrix>("matrix", sol::no_constructor);
    matrix["right"] = &::rfg::matrix::right;
    matrix["up"] = &::rfg::matrix::up;
    matrix["forward"] = &::rfg::matrix::forward;
}

void bind_matrix43(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();
    auto matrix43 = types.new_usertype<::rfg::matrix43>("matrix43", sol::no_constructor);
    matrix43["rotation"] = &::rfg::matrix43::m_rotation;
    matrix43["translation"] = &::rfg::matrix43::m_translation;
}

} // namespace lua::bindings::rfg