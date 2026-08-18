#include "address.hpp"

#include "patch/main.hpp"

namespace utils::address {
uintptr_t convert(utils::address::offset offset) {
    uintptr_t new_offset;

    switch (g_game_version) {
    case game_version::gog:
        new_offset = offset.gog;
        break;
    case game_version::steam:
        new_offset = offset.steam;
        break;
    }

    new_offset -= 0x400000;
    return (uintptr_t)g_game_module_base + new_offset;
}
} // namespace utils::address
