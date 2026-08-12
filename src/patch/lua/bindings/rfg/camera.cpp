#include "camera.hpp"

#include "patch/rfg/camera.hpp"

#include <sol/sol.hpp>

namespace lua::bindings::rfg {
void bind_camera(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();

    auto camera = types.new_usertype<::rfg::camera>("camera");
    camera["position"] = &::rfg::camera::real_pos;
    camera["orientation"] = &::rfg::camera::real_orient;
}

} // namespace lua::bindings::rfg
