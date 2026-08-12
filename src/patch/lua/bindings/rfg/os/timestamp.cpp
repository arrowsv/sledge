#include "patch/rfg/os/timestamp.hpp"

#include <sol/sol.hpp>

namespace rfg {
void bind_timestamp(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto timestamp = table.new_usertype<rfg::timestamp>("timestamp");
    timestamp["value"] = &rfg::timestamp::value;
}

void bind_timestamp_percent(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();
    auto timestamp_percent = table.new_usertype<rfg::timestamp_percent>(
        "timestamp_percent", sol::base_classes, sol::bases<rfg::timestamp>());
    timestamp_percent["set_milliseconds"] = &rfg::timestamp_percent::set_milliseconds;
}

} // namespace rfg