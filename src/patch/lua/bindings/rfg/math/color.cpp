#include "patch/rfg/math/color.hpp"
#include <sol/sol.hpp>

namespace rfg {
void bind_color(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto color = table.new_usertype<rfg::color>("color", sol::no_constructor);
    color["red"] = &rfg::color::red;
    color["green"] = &rfg::color::green;
    color["blue"] = &rfg::color::blue;
    color["alpha"] = &rfg::color::alpha;
}

void bind_color_float(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto color_float = table.new_usertype<rfg::color_float>("color_float", sol::no_constructor);
    color_float["red"] = &rfg::color_float::red;
    color_float["green"] = &rfg::color_float::green;
    color_float["blue"] = &rfg::color_float::blue;
    color_float["alpha"] = &rfg::color_float::alpha;
}

} // namespace rfg
