#include "patch/rfg/os/string.hpp"
#include <sol/sol.hpp>

namespace rfg {
void bind_checksum_string(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>().new_usertype<rfg::checksum_string>(
        "checksum_string");
    table["checksum"] = &rfg::checksum_string::checksum;
}

void bind_checksum_string_pair(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>().new_usertype<rfg::checksum_string_pair>(
        "checksum_string_pair");
    table["string"] = &rfg::checksum_string_pair::string;
    table["string_checksum"] = &rfg::checksum_string_pair::string_checksum;
}
} // namespace rfg
