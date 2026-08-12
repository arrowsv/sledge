#include "hooks.hpp"
#include "gameplay.hpp"
#include "misc.hpp"
#include "render.hpp"
#include "xml.hpp"

namespace hooks {
void apply() {
    misc::apply();
    render::apply();
    gameplay::apply();
    xml::apply();
}
} // namespace hooks
