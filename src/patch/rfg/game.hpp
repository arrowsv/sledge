#pragma once

#include "math/color.hpp"
#include "patch/rfg/player.hpp"
#include "patch/utils/memory.hpp"

#include <cstdint>

namespace rfg {

enum alert_level {
    ALERT_LEVEL_INVALID = 0xFFFFFFFF,
    ALERT_LEVEL_GREEN = 0x0,
    ALERT_LEVEL_YELLOW = 0x1,
    ALERT_LEVEL_ORANGE = 0x2,
    ALERT_LEVEL_RED = 0x3,
    NUM_ALERT_LEVELS = 0x4,
};

enum game_state {
    GS_MAINMENU = 0x0,
    GS_GAMEPLAY = 0x1,
    GS_LOAD = 0x2,
    GS_BOOT = 0x3,
    GS_MULTI_INIT = 0x4,
    GS_MULTI_SHUTDOWN = 0x5,
    GS_CONNECTING_TO_INVITE = 0x6,
    GS_MAINMENU_OPTIONS = 0x7,
    GS_MAINMENU_OPTIONS_DISPLAY = 0x8,
    GS_MAINMENU_OPTIONS_AUDIO = 0x9,
    GS_MAINMENU_OPTIONS_LIVE = 0xA,
    GS_MAINMENU_OPTIONS_LIVE_QUICKMATCH = 0xB,
    GS_MAINMENU_OPTIONS_GAME_OPTIONS = 0xC,
    GS_MAINMENU_OPTIONS_EXTRAS = 0xD,
    GS_CHEATS = 0xE,
    GS_INGAME_OPTIONS = 0xF,
    GS_PLAYER_DEATH_OPTIONS = 0x10,
    GS_SONY_OPTIONS = 0x11,
    GS_CONTROLLER_OPTIONS = 0x12,
    GS_WRECKING_CREW_MAIN_MENU = 0x13,
    GS_WRECKING_CREW_CHARACTER_SELECT = 0x14,
    GS_WRECKING_CREW_SCOREBOARD = 0x15,
    GS_MULTIPLAYER_LIVE = 0x16,
    GS_MULTIPLAYER_CHANGE_MATCHMAKING = 0x17,
    GS_MULTIPLAYER_SEARCH_MATCHMAKING = 0x18,
    GS_MULTIPLAYER_GAME_LOBBY = 0x19,
    GS_MULTIPLAYER_PARTY_LOBBY = 0x1A,
    GS_MULTIPLAYER_PARTY_OPTIONS = 0x1B,
    GS_MULTIPLAYER_SYSLINK = 0x1C,
    GS_MULTIPLAYER_SYSLINK_FIND_SERVERS = 0x1D,
    GS_MULTIPLAYER_CHANGE_GAME_OPTIONS = 0x1E,
    GS_MULTIPLAYER_PLAYER_SELECT = 0x1F,
    GS_MULTIPLAYER_XP_TALLY = 0x20,
    GS_MULTIPLAYER_RESULTS = 0x21,
    GS_MULTIPLAYER_SCOREBOARD = 0x22,
    GS_MULTIPLAYER_STATS = 0x23,
    GS_MULTIPLAYER_TUTORIALS = 0x24,
    GS_INGAME_FULLSCREEN_MAP = 0x25,
    GS_INGAME_MISSION_BRIEFING = 0x26,
    GS_INGAME_ACTIVITY_BRIEFING = 0x27,
    GS_INGAME_MISSION_COMPLETE = 0x28,
    GS_INGAME_ACTIVITY_COMPLETE = 0x29,
    GS_INGAME_UPGRADES_HUD = 0x2A,
    GS_INGAME_HANDBOOK_HUD = 0x2B,
    GS_INGAME_RAIL_DRIVER_HUD = 0x2C,
    GS_INGAME_DISTRICT_LIVERATION = 0x2D,
    GS_INGAME_WEAPON_CABINET = 0x2E,
    GS_LOAD_CUTSCENE = 0x2F,
    GS_MAINMENU_IDLE = 0x30,
    GS_VIDEO_CUTSCENE_PLAY = 0x31,
    GS_SAVE_LOAD_SCREEN = 0x32,
    GS_PS3_DLC = 0x33,
    GS_VIEW_DLC_SCREEN = 0x34,
    GS_STATS_SCREEN = 0x35,
    GS_CREDITS = 0x36,
    GS_VERIFY_SAVEGAME = 0x37,
    GS_SHUTDOWN = 0x38,
    GS_DLC_INIT = 0x39,
    GS_DLC_SHUTDOWN = 0x3A,
    GS_WC_INIT = 0x3B,
    GS_WC_SHUTDOWN = 0x3C,
    GS_RESOLUTION_CHANGE = 0x3D,
    GS_QUICK_PAUSE = 0x3E,
    GS_MULTIPLAYER_LIVE_FIND_SERVERS = 0x3F,
};

enum game_clock_time_of_day : uint32_t {
    GC_INVALID = 0xffffffff,
    GC_DAY = 0x0,
    GC_NIGHT = 0x1,
    GC_TIME_OF_DAY_COUNT = 0x2
};

struct game_clock {
    unsigned __int16 year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t day_of_week;
    float time_scale;
    unsigned int current_day_ticks;
};

struct wind_range_info {
    float min_speed;
    float max_speed;
    int32_t min_time;
    int32_t max_time;
    float skip_up_percent;
    float skip_down_percent;
    float direction_percent;
    float drop_to_zero_percent;
};

struct rfg_wind_info {
    uint8_t wind_active;
    float wind_mph;
    float wind_dest_mph;
    float wind_dir;
    float wind_dest_dir;
    int32_t min_ramp_time;
    int32_t max_ramp_time;
    int32_t ramp_time;
    int32_t num_wind_ranges;
    struct wind_range_info wind_ranges[0x8];
};

struct rfg_weather_info {
    struct rfg_wind_info wind;
};

REF_FUNC(ui_add_secondary_message,
         rfg::hud_message_handle __cdecl(const wchar_t* text, float display_time,
                                         bool animated_background, bool force_redisplay),
         0x008d8270);

REF_FUNC(get_alert_level, rfg::alert_level __cdecl(), 0x75D580);
REF_FUNC(set_alert_level, void __cdecl(rfg::alert_level alert_level), 0x7AA6B0);

REF_FUNC(get_alert_level_cap, void __cdecl(rfg::alert_level* minimum, rfg::alert_level* maximum),
         0x75D580);
REF_FUNC(set_alert_level_cap,
         rfg::alert_level __cdecl(rfg::alert_level minimum, rfg::alert_level maximum), 0x007aa6e0);
REF_FUNC(release_alert_level_cap, void __cdecl(), 0x0075d5f0);

REF_FUNC(game_clock_set_time, void __cdecl(uint32_t hours, uint32_t minutes, uint32_t seconds),
         0x7C16F0);
REF_FUNC(game_clock_get_time_period, rfg::game_clock_time_of_day __cdecl(), 0x007c1560);
REF_VAR(g_game_time_should_update, bool, 0x165BBE8);
REF_VAR(g_game_clock, rfg::game_clock, 0x25044AC);

REF_FUNC(gameseq_get_state, rfg::game_state __cdecl(), 0x7BFC70);
REF_FUNC(gameseq_state_is_active, bool __cdecl(rfg::game_state state), 0x007bfc90);

REF_FUNC(game_pause, void __cdecl(bool mute_music), 0x007c1620);
REF_FUNC(game_unpause, void __cdecl(), 0x007c1650);
REF_FUNC(game_is_paused, bool __cdecl(), 0x007c1610);

// Graphics/Render
REF_FUNC(is_hud_hidden, bool __cdecl(), 0x00841b10);
REF_FUNC(set_hud_hidden, void __cdecl(bool hidden), 0x00841ae0);
REF_FUNC(is_fog_enabled, bool __cdecl(), 0x007c2c40);
REF_FUNC(set_fog_enabled, void __cdecl(bool enabled), 0x007c2c50);

// Weather
REF_FUNC(weather_wind_start, bool __cdecl(), 0x00beccb0);
REF_FUNC(weather_wind_stop, void __cdecl(), 0x00becdb0);
REF_VAR(g_weather_stats, rfg::rfg_weather_info, 0x038b1f90);

REF_VAR(g_frames_per_second, float, 0x151856c);
REF_VAR(g_frametime_minimum, float, 0x1518574);

REF_VAR(g_exit_startup_videos, bool, 0x2C071C2);
REF_VAR(g_multiplayer, bool, 0x02fea588);

REF_VAR(g_player_input_disabled, bool, 0x01e299b9);
REF_VAR(g_player_camera_input_disabled, bool, 0x01e299ba);

// Player
REF_VAR(g_unlimited_ammo, bool, 0x3881CB6);
REF_VAR(g_unlimited_magazine_ammo, bool, 0x3881CBC);
REF_VAR(g_vehicle_max_speed, float, 0x16B9434);

// World
REF_VAR(g_fog_color, rfg::color_float, 0x0165d8b8);
} // namespace rfg
