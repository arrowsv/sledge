#include "game.hpp"

#include "patch/hooks/gameplay.hpp"
#include "patch/rfg/game.hpp"
#include "patch/rfg/player.hpp"
#include "patch/rfg/camera.hpp"
#include "patch/hooks/render.hpp"
#include "patch/utils/string.hpp"

#include <sol/sol.hpp>

struct game_type {};

namespace lua::bindings::rfg {

void bind_types(sol::state_view& lua) {
    auto types = lua["types"].get_or_create<sol::table>();

    auto game_clock = types.new_usertype<::rfg::game_clock>("game_clock");
    game_clock["year"] = &::rfg::game_clock::year;
    game_clock["month"] = &::rfg::game_clock::month;
    game_clock["day"] = &::rfg::game_clock::day;
    game_clock["hours"] = &::rfg::game_clock::hours;
    game_clock["minutes"] = &::rfg::game_clock::minutes;
    game_clock["seconds"] = &::rfg::game_clock::seconds;
    game_clock["day_of_week"] = &::rfg::game_clock::day_of_week;
    game_clock["time_scale"] = &::rfg::game_clock::time_scale;
    game_clock["current_day_ticks"] = &::rfg::game_clock::current_day_ticks;
}

void bind_defines(sol::state_view& lua) {
    auto defines = lua["defines"].get_or_create<sol::table>();

    auto time_of_day = defines.create_named("time_of_day");
    time_of_day["day"] = ::rfg::game_clock_time_of_day::GC_DAY;
    time_of_day["night"] = ::rfg::game_clock_time_of_day::GC_NIGHT;

    auto alert_level = defines.create_named("alert_level");
    alert_level["green"] = ::rfg::alert_level::ALERT_LEVEL_GREEN;
    alert_level["yellow"] = ::rfg::alert_level::ALERT_LEVEL_YELLOW;
    alert_level["orange"] = ::rfg::alert_level::ALERT_LEVEL_ORANGE;
    alert_level["red"] = ::rfg::alert_level::ALERT_LEVEL_RED;
}

void bind_player(sol::usertype<game_type>& game) {
    game["get_player"] = []() -> ::rfg::player* { return ::rfg::get_local_player(); };
    game["is_in_gameplay"] = []() -> bool {
        return ::rfg::gameseq_state_is_active(::rfg::game_state::GS_GAMEPLAY);
    };
}

void bind_camera(sol::usertype<game_type>& game) {
    game["get_camera"] = []() -> ::rfg::camera* { return ::rfg::g_camera(); };
    game["overriding_camera_position"] = sol::property(
        []() { return hooks::gameplay::g_camera_overriding_position; },
        [](bool overriding) { hooks::gameplay::g_camera_overriding_position = overriding; });
    game["overriding_camera_orientation"] = sol::property(
        []() { return hooks::gameplay::g_camera_overriding_orientation; },
        [](bool overriding) { hooks::gameplay::g_camera_overriding_orientation = overriding; });
}

void bind_time(sol::usertype<game_type>& game) {
    game["time_frozen"] =
        sol::property([]() { return !*::rfg::g_game_time_should_update(); },
                      [](bool frozen) { *::rfg::g_game_time_should_update() = !frozen; });
    game["get_time"] = []() { return *::rfg::g_game_clock(); };
    game["get_time_period"] = []() { return ::rfg::game_clock_get_time_period(); };
    game["get_time_of_day"] = []() {
        auto time = *::rfg::g_game_clock();
        return std::make_tuple(time.hours, time.minutes, time.seconds);
    };
    game["set_time_of_day"] = [](int32_t hours, int32_t minutes, int32_t seconds) {
        ::rfg::game_clock_set_time(hours, minutes, seconds);
    };
}

void bind_alert_level(sol::usertype<game_type>& game) {
    game["get_alert_level"] = []() { return ::rfg::get_alert_level(); };
    game["set_alert_level"] = [](::rfg::alert_level alert_level) {
        ::rfg::set_alert_level(alert_level);
    };
    game["get_alert_level_cap"] = []() {
        ::rfg::alert_level minimum;
        ::rfg::alert_level maximum;
        ::rfg::get_alert_level_cap(&minimum, &maximum);
        return std::make_tuple(minimum, maximum);
    };
    game["set_alert_level_cap"] = [](::rfg::alert_level minimum, ::rfg::alert_level maximum) {
        ::rfg::set_alert_level_cap(minimum, maximum);
    };
    game["release_alert_level_cap"] = []() { ::rfg::release_alert_level_cap(); };
}

void bind_input(sol::usertype<game_type>& game) {
    game["is_key_down"] = [](utils::os::key key) { return hooks::render::is_key_down(key); };
    game["is_key_just_pressed"] = [](utils::os::key key) {
        return hooks::render::is_key_just_pressed(key);
    };
    game["is_key_just_released"] = [](utils::os::key key) {
        return hooks::render::is_key_just_released(key);
    };

    game["input_enabled"] =
        sol::property([]() -> bool { return !*::rfg::g_player_input_disabled(); },
                      [](bool enabled) { *::rfg::g_player_input_disabled() = !enabled; });

    game["camera_input_enabled"] =
        sol::property([]() -> bool { return !*::rfg::g_player_camera_input_disabled(); },
                      [](bool enabled) { *::rfg::g_player_camera_input_disabled() = !enabled; });
}

void bind_ui(sol::usertype<game_type>& game, sol::state_view& lua) {
    game["show_message"] = [&lua](const std::string& text, sol::optional<sol::table> options) {
        sol::table options_table = options ? options.value() : lua.create_table();

        float duration = options_table.get_or("duration", 3);
        bool animated = options_table.get_or("animated", false);

        ::rfg::ui_add_secondary_message(utils::string::widen_string(text).c_str(), duration,
                                        animated, false);
    };
}

void bind_settings(sol::usertype<game_type>& game) {
    game["unlimited_ammo"] =
        sol::property([]() { return *::rfg::g_unlimited_ammo(); },
                      [](bool enabled) { *::rfg::g_unlimited_ammo() = enabled; });
    game["unlimited_magazine_ammo"] =
        sol::property([]() { return *::rfg::g_unlimited_magazine_ammo(); },
                      [](bool enabled) { *::rfg::g_unlimited_magazine_ammo() = enabled; });

    game["fog_visible"] = sol::property([]() { return ::rfg::is_fog_enabled(); },
                                        [](bool visible) { ::rfg::set_fog_enabled(visible); });
    game["hud_visible"] = sol::property([]() { return !::rfg::is_hud_hidden(); },
                                        [](bool visible) { ::rfg::set_hud_hidden(!visible); });

    game["wind_visible"] =
        sol::property([]() -> bool { return ::rfg::g_weather_stats()->wind.wind_active; },
                      [](bool visible) {
                          if (visible) {
                              ::rfg::weather_wind_start();
                          } else {
                              ::rfg::weather_wind_stop();
                          }
                      });
    
    game["pause"] = []() { ::rfg::game_pause(true); };
    game["unpause"] = []() { ::rfg::game_unpause(); };
    game["is_paused"] = []() -> bool { return ::rfg::game_is_paused(); };
}

void bind_game(sol::state_view& lua) {
    lua["game"] = game_type{};

    auto types = lua["types"].get_or_create<sol::table>();
    auto game = types.new_usertype<game_type>("game");

    bind_types(lua);
    bind_defines(lua);

    // Functions/properties
    bind_player(game);
    bind_camera(game);
    bind_time(game);
    bind_alert_level(game);
    bind_input(game);
    bind_ui(game, lua);
    bind_settings(game);
}
} // namespace lua::bindings::rfg
