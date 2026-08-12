#include "main.hpp"

#include "common/config.hpp"
#include "common/constants.hpp"
#include "common/logging.hpp"
#include "common/mods.hpp"
#include "common/utils/os.hpp"
#include "gui/gui.hpp"
#include "hooks/hooks.hpp"
#include "lua/manager.hpp"

#include <MinHook.h>
#include <filesystem>
#include <magic_enum.hpp>
#include <picosha2.h>
#include <plog/Log.h>

game_version g_game_version;
HMODULE g_sledge_module_base;
HMODULE g_game_module_base;
HWND g_game_window_handle;

const std::unordered_map<std::string, game_version> version_hashes = {
    {"7a82d2d0f425af5e75d8ffbce12fac53eb5ca9cd812731ccf5a29697e906af0e",
     game_version::gog}, // 1.0_Fix - 2025-01-30
                         // cs:4931 - 2018-09-20
    {"0d52039e7f2d3f25a4be52a2aba83919456fb3f00e52e75051726247471a2df4",
     game_version::steam} // 10642344 - 2023-02-26
                          // 3121288 - 2018-09-20
};

bool verify_game_version() {
    auto game_executable = utils::os::get_module_directory(g_game_module_base) / "rfg.exe";

    std::ifstream file(game_executable, std::ios::binary);
    std::vector<unsigned char> hash(picosha2::k_digest_size);
    if (!file.is_open()) {
        utils::os::show_message_error("Failed to open rfg.exe to verify game version.");
        return false;
    }

    picosha2::hash256(file, hash.begin(), hash.end());
    std::string file_hash = picosha2::bytes_to_hex_string(hash.begin(), hash.end());

    auto it = version_hashes.find(file_hash);
    if (it != version_hashes.end()) {
        g_game_version = it->second;
        PLOG_INFO << "Game version: " << std::string(magic_enum::enum_name(g_game_version));

        if (g_game_version == game_version::steam) {
            utils::os::show_message_error("Sledge " + std::string(constants::version) +
                                          " is not compatible with Steam.");
            return false;
        }

        return true;
    }

    utils::os::show_message_error("Unknown hash for rfg.exe. Got: \'" + file_hash + "\'.");
    return false;
}

extern "C" __declspec(dllexport) bool initialize() {
    try {
        auto sledge_directory = utils::os::get_module_directory(g_sledge_module_base);

        logging::initialize(sledge_directory, "sledge");

        PLOG_DEBUG << "Game module base: " << g_game_module_base;
        PLOG_DEBUG << "Sledge module base: " << g_sledge_module_base;

        if (!verify_game_version())
            return false;

        config::get().initialize(sledge_directory);
        mods::manager::get().initialize(sledge_directory / "mods");
        config::get().save();

        auto enabled_mods = mods::manager::get().get_enabled_mods();
        if (!enabled_mods.empty()) {
            std::string enabled_mods_str = "";
            for (auto& mod : enabled_mods) {
                enabled_mods_str +=
                    std::format("\n{} - Name: {} - Version: {}", mod.id, mod.name, mod.version);
            }
            PLOG_INFO << "Enabled mods:" << enabled_mods_str;
        }

        gui::manager::get().initialize();
        lua::manager::get().initialize();

        hooks::apply();

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
