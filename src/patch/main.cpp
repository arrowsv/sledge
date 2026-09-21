#include "main.hpp"

#include "common/config.hpp"
#include "common/game_version.hpp"
#include "common/logging.hpp"
#include "common/mods.hpp"
#include "common/utils/os.hpp"
#include "gui/manager.hpp"
#include "lua/manager.hpp"
#include "patch/graphics/graphics.hpp"
#include "patch/input/input.hpp"
#include "patch/misc/misc.hpp"

#include <filesystem>
#include <spdlog/spdlog.h>

HMODULE g_sledge_module_base;
HMODULE g_game_module_base;
HWND g_game_window_handle;

extern "C" __declspec(dllexport) bool initialize() {
    try {
        auto game_directory = utils::os::get_module_directory(g_game_module_base);
        identify_game_version(game_directory / "rfg.exe");
        if (g_game_version == game_version::unknown) {
            return false;
        }

        auto sledge_directory = utils::os::get_module_directory(g_sledge_module_base);
        logging::initialize(sledge_directory, "sledge");
        config::get().initialize(sledge_directory);
        logging::update_level();

        mods::manager::get().initialize(sledge_directory / "mods");
        config::get().save();

        const auto enabled_mods = mods::manager::get().get_enabled_mods();
        if (!enabled_mods.empty()) {
            std::string enabled_mods_str = "";
            for (const auto& mod : enabled_mods) {
                enabled_mods_str +=
                    std::format("\n{} ({}) - {}", mod.id, mod.name, mod.version);
            }
            spdlog::info("Enabled mods: {}", enabled_mods_str);
        }

        gui::manager::get().initialize();
        lua::manager::get().initialize();

        misc::apply_patches();
        graphics::apply_patches();
        input::apply_patches();

        return true;
    } catch (const std::exception& e) {
        utils::os::show_message_error("Unhandled exception during initialization: " +
                                      std::string(e.what()));
        return false;
    } catch (...) {
        utils::os::show_message_error("Unknown exception during initialization.");
        return false;
    }
}

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(instance);
        g_sledge_module_base = instance;
        g_game_module_base = GetModuleHandle(nullptr);
    }
    return TRUE;
}
