#include "core.hpp"

#include "sledge/gui.hpp"
#include "sledge/mod.hpp"
#include "sledge/xml.hpp"
#include "sledge/event.hpp"
#include "sledge/key.hpp"

#include "rfg/math/vector.hpp"
#include "rfg/math/matrix.hpp"
#include "rfg/camera.hpp"
#include "rfg/game.hpp"
#include "rfg/object.hpp"
#include "rfg/human.hpp"
#include "rfg/player.hpp"

#include <sol/sol.hpp>

namespace lua::bindings {
void bind_all(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();
    auto defines = lua["defines"].get_or_create<sol::table>();

    // sledge
    sledge::bind_mod(lua);
    sledge::bind_gui(lua);
    sledge::bind_xml(lua);
    sledge::bind_event(lua);
    sledge::bind_key(lua);

    // rfg/math
    rfg::bind_vector(lua);
    rfg::bind_vector2(lua);
    rfg::bind_vector4(lua);
    rfg::bind_matrix(lua);

    // rfg
    rfg::bind_camera(lua);
    rfg::bind_game(lua);
    rfg::bind_object(lua);
    rfg::bind_human(lua);
    rfg::bind_player(lua);
}
} // namespace lua::bindings
