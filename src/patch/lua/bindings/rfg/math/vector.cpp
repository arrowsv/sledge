#include "patch/rfg/math/vector.hpp"

#include <sol/sol.hpp>

namespace lua::bindings::rfg {
void bind_vector(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();

    auto vector = types.new_usertype<::rfg::vector>(
        "vector", sol::constructors<::rfg::vector(), ::rfg::vector(const ::rfg::vector&),
                                    ::rfg::vector(float), ::rfg::vector(float, float, float)>());

    vector["x"] = &::rfg::vector::x;
    vector["y"] = &::rfg::vector::y;
    vector["z"] = &::rfg::vector::z;

    vector["magnitude"] = &::rfg::vector::magnitude;
    vector["unit_vector"] = &::rfg::vector::unit_vector;

    vector[sol::meta_function::addition] = [](const ::rfg::vector& a, const ::rfg::vector& b) {
        return ::rfg::vector(a.x + b.x, a.y + b.y, a.z + b.z);
    };

    vector[sol::meta_function::subtraction] = [](const ::rfg::vector& a, const ::rfg::vector& b) {
        return ::rfg::vector(a.x - b.x, a.y - b.y, a.z - b.z);
    };

    vector[sol::meta_function::equal_to] = [](const ::rfg::vector& a, const ::rfg::vector& b) {
        return (a.x == b.x && a.y == b.y && a.z == b.z);
    };

    vector[sol::meta_function::multiplication] = sol::overload(
        [](const ::rfg::vector& a, const ::rfg::vector& b) -> float {
            return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
        },
        [](const ::rfg::vector& v, float scalar) {
            return ::rfg::vector(v.x * scalar, v.y * scalar, v.z * scalar);
        },
        [](float scalar, const ::rfg::vector& v) {
            return ::rfg::vector(v.x * scalar, v.y * scalar, v.z * scalar);
        });

    vector[sol::meta_function::division] = sol::overload([](const ::rfg::vector& v, float scalar) {
        return ::rfg::vector(v.x / scalar, v.y / scalar, v.z / scalar);
    });
}

void bind_vector2(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();
    auto vector2 = types.new_usertype<::rfg::vector2>(
        "vector2", sol::constructors<::rfg::vector2(), ::rfg::vector2(const ::rfg::vector2&),
                                     ::rfg::vector2(float), ::rfg::vector2(float, float)>());
    vector2["x"] = &::rfg::vector2::x;
    vector2["y"] = &::rfg::vector2::y;
    vector2["scale"] = &::rfg::vector2::scale;
}

void bind_vector4(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();
    auto vector4 = types.new_usertype<::rfg::vector4>("vector4");
    vector4["x"] = &::rfg::vector4::x;
    vector4["y"] = &::rfg::vector4::y;
    vector4["z"] = &::rfg::vector4::z;
    vector4["w"] = &::rfg::vector4::w;
}

void bind_bbox(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();
    auto bbox = types.new_usertype<::rfg::bbox>("bbox");
    bbox["min"] = &::rfg::bbox::min;
    bbox["max"] = &::rfg::bbox::max;
}

void bind_plane(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();
    auto plane = types.new_usertype<::rfg::plane>("plane");
    plane["normal"] = &::rfg::plane::normal;
    plane["offset"] = &::rfg::plane::offset;
}

void bind_cubic_bezier_spline(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();
    auto cubic_bezier_spline =
        types.new_usertype<::rfg::cubic_bezier_spline>("cubic_bezier_spline", sol::no_constructor);
    cubic_bezier_spline["knots"] = &::rfg::cubic_bezier_spline::knots;
    cubic_bezier_spline["incoming_handles"] = &::rfg::cubic_bezier_spline::incoming_handles;
    cubic_bezier_spline["outgoing_handles"] = &::rfg::cubic_bezier_spline::outgoing_handles;
    cubic_bezier_spline["num_knots"] = &::rfg::cubic_bezier_spline::num_knots;
}

void bind_short_quaternion(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();
    auto short_quaternion = types.new_usertype<::rfg::short_quaternion>("short_quaternion");
    short_quaternion["x"] = &::rfg::short_quaternion::x;
    short_quaternion["y"] = &::rfg::short_quaternion::y;
    short_quaternion["z"] = &::rfg::short_quaternion::z;
    short_quaternion["w"] = &::rfg::short_quaternion::w;
}

} // namespace lua::bindings::rfg
