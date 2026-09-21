#include "injector.hpp"

#include "common/config.hpp"
#include "common/game_version.hpp"
#include "common/utils/os.hpp"

#include <fstream>
#include <windows.h>

namespace {
    std::filesystem::path game_dir;
    std::filesystem::path game_exe;

    bool is_running_under_wine() {
        HMODULE ntdll = GetModuleHandleA("ntdll.dll");
        return ntdll && GetProcAddress(ntdll, "wine_get_version") != nullptr;
    }

    bool launch_steam() {
        std::string uri = "steam://run/667720";

        INT_PTR result = reinterpret_cast<INT_PTR>(
            ShellExecute(NULL, "open", uri.c_str(), NULL, NULL, SW_SHOWNORMAL));
        if (result > 32) {
            return true;
        }

        if (is_running_under_wine()) {
            std::string params = "/unix /usr/bin/xdg-open \"" + uri + "\"";
            result = reinterpret_cast<INT_PTR>(
                ShellExecute(NULL, "open", "start", params.c_str(), NULL, SW_SHOWNORMAL));
            if (result > 32) {
                return true;
            }
        }
        return false;
    }

    bool launch_gog() {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        if (CreateProcessA(game_exe.string().c_str(), nullptr, nullptr, nullptr, FALSE, 0, NULL,
                           game_dir.string().c_str(), &si, &pi)) {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            return true;
        }

        return false;
    }
}

void launch(bool vanilla) {
    auto found_sledge_dir = utils::os::find_sledge_directory();
    if (!found_sledge_dir) {
        utils::os::show_message_error(
            "Failed to launch game: Sledge directory couldn't be found."
            "\n\nSledge must be placed in the game's root folder or 'sledge' "
            "subdirectory.");
        return;
    }

    auto found_game_dir = utils::os::find_game_directory();
    if (!found_game_dir) {
        utils::os::show_message_error("Failed to launch game: game directory couldn't be found."
                                      "\n\nSledge must be placed within the game's root folder "
                                      "or 'sledge' subdirectory.");
        return;
    }
    game_dir = found_game_dir.value();
    game_exe = game_dir / "rfg.exe";

    identify_game_version(game_exe);
    if (g_game_version == game_version::unknown) {
        return;
    }

    auto vanilla_file_path = found_sledge_dir.value() / "sledge_launch_vanilla.txt";
    if (vanilla) {
        std::ofstream vanilla_file(vanilla_file_path);
        if (!vanilla_file.is_open()) {
            utils::os::show_message_error(
                std::format("Failed to launch game as vanilla: unable to create file '{}'.",
                            vanilla_file_path.string()));
            return;
        }
        vanilla_file << "This file was created by Sledge and will be deleted automatically."
                     << std::endl;
        vanilla_file.close();
    } else {
        if (std::filesystem::exists(vanilla_file_path)) {
            try {
                std::filesystem::remove(vanilla_file_path);
            } catch (const std::filesystem::filesystem_error& e) {
                utils::os::show_message_error(
                    std::format("Error deleting '{}': {}", vanilla_file_path.string(), e.what()));
            }
        }
    }

    bool launched = false;
    if (g_game_version == game_version::steam) {
        launched = launch_steam();
    } else if (g_game_version == game_version::gog) {
        launched = launch_gog();
    }

    if (!launched) {
        utils::os::show_message_error("Game failed to launch.");
        return;
    }

    if (!config::get().sledge.keep_launcher_open) {
        std::exit(0);
    }
}