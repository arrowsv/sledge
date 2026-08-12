#include "patch/rfg/object.hpp"
#include "patch/rfg/human.hpp"
#include "patch/rfg/player.hpp"
#include "patch/rfg/vehicle.hpp"
#include "patch/rfg/world.hpp"

#include <sol/sol.hpp>

namespace lua::bindings::rfg {
void bind_object_functions(sol::state_view& lua) {
    auto table = lua["game"].get_or_create<sol::table>();

    table["get_object_from_handle"] = [](uint32_t handle) -> ::rfg::object* {
        for (int i = 0; i < ::rfg::g_world()->all_objects.size(); i++) {
            if (::rfg::g_world()->all_objects[i]->handle == handle) {
                return ::rfg::g_world()->all_objects[i];
            }
        }
        return nullptr;
    };

    table["apply_linear_impulse"] = [](uint32_t handle, const ::rfg::vector* impulse) {
        ::rfg::havok_body_apply_linear_impulse(handle, impulse);
    };

    table["apply_point_impulse"] = [](uint32_t handle, const ::rfg::vector* impulse,
                                      const ::rfg::vector* position) {
        ::rfg::havok_body_apply_point_impulse(handle, impulse, position);
    };
}

void bind_object_type(sol::state_view& lua) {
    auto defines = lua["defines"].get_or_create<sol::table>();

    auto object_type = defines.create_named("object_type");
    object_type["undefined"] = ::rfg::object_type::OT_UNDEFINED;
    object_type["human"] = ::rfg::object_type::OT_HUMAN;
    object_type["item"] = ::rfg::object_type::OT_ITEM;
    object_type["mover"] = ::rfg::object_type::OT_MOVER;
    object_type["vehicle"] = ::rfg::object_type::OT_VEHICLE;
}

void bind_object_sub_type(sol::state_view& lua) {
    auto defines = lua["defines"].get_or_create<sol::table>();

    auto object_sub_type = defines.create_named("object_sub_type");
    object_sub_type["undefined"] = ::rfg::object_sub_type::OT_SUB_UNDEFINED;
    object_sub_type["mover_general"] = ::rfg::object_sub_type::OT_SUB_MOVER_GENERAL;
    object_sub_type["mover_rfg"] = ::rfg::object_sub_type::OT_SUB_MOVER_RFG;
    object_sub_type["human_npc"] = ::rfg::object_sub_type::OT_SUB_HUMAN_NPC;
    object_sub_type["human_player"] = ::rfg::object_sub_type::OT_SUB_HUMAN_PLAYER;
    object_sub_type["vehicle_automobile"] = ::rfg::object_sub_type::OT_SUB_VEHICLE_AUTO;
    object_sub_type["vehicle_flyer"] = ::rfg::object_sub_type::OT_SUB_VEHICLE_FLYER;
    object_sub_type["vehicle_walker"] = ::rfg::object_sub_type::OT_SUB_VEHICLE_WALKER;
    object_sub_type["item_weapon"] = ::rfg::object_sub_type::OT_SUB_ITEM_WEAPON;
    object_sub_type["item_projectile"] = ::rfg::object_sub_type::OT_SUB_ITEM_PROJECTILE;
    object_sub_type["item_multi_flag"] = ::rfg::object_sub_type::OT_SUB_ITEM_MULTI_FLAG;
    object_sub_type["item_multi_backpack"] = ::rfg::object_sub_type::OT_SUB_ITEM_MULTI_BACKPACK;
}

void bind_object(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();

    bind_object_type(lua);
    bind_object_sub_type(lua);

    auto object = types.new_usertype<::rfg::object>("object", sol::no_constructor);
    object["position"] = sol::readonly(&::rfg::object::position);
    object["orientation"] = sol::readonly(&::rfg::object::orient);
    object["child"] = sol::readonly(&::rfg::object::child_ptr);
    object["child_next"] = sol::readonly(&::rfg::object::child_next);
    object["child_previous"] = sol::readonly(&::rfg::object::child_prev);
    object["havok_handle"] = sol::readonly(&::rfg::object::havok_handle);
    object["handle"] = sol::readonly(&::rfg::object::handle);
    object["parent"] = sol::readonly(&::rfg::object::parent);
    object["type"] = sol::readonly_property(
        [](::rfg::object& self) -> int { return static_cast<int>(self.obj_type); });
    object["sub_type"] = sol::readonly_property(
        [](::rfg::object& self) -> int { return static_cast<int>(self.sub_type); });

    // Functions
    object["to_human"] = [](::rfg::object& self) -> ::rfg::human* {
        return static_cast<::rfg::human*>(&self);
    };
    object["to_player"] = [](::rfg::object& self) -> ::rfg::player* {
        return static_cast<::rfg::player*>(&self);
    };
    object["to_vehicle"] = [](::rfg::object& self) -> ::rfg::vehicle* {
        return static_cast<::rfg::vehicle*>(&self);
    };
    object["to_walker"] = [](::rfg::object& self) -> ::rfg::walker* {
        return static_cast<::rfg::walker*>(&self);
    };
    object["to_flyer"] = [](::rfg::object& self) -> ::rfg::flyer* {
        return static_cast<::rfg::flyer*>(&self);
    };
    object["to_automobile"] = [](::rfg::object& self) -> ::rfg::automobile* {
        return static_cast<::rfg::automobile*>(&self);
    };
    object["set_visible"] = [](::rfg::object& self, bool visible) {
        ::rfg::object_set_visibility_plus_children(&self, visible);
    };
}
} // namespace lua::bindings::rfg
