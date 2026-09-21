#include "os.hpp"

#include <fstream>
#include <windows.h>
#include <nfd.h>
#include <magic_enum.hpp>
#include <spdlog/spdlog.h>

namespace utils::os {
    void show_message_info(const std::string& message) {
        spdlog::info(message);
        MessageBoxA(NULL, message.c_str(), "Sledge", MB_OK | MB_ICONINFORMATION);
    }

    void show_message_error(const std::string& message) {
        spdlog::error(message);
        MessageBoxA(NULL, message.c_str(), "Sledge", MB_OK | MB_ICONERROR);
    }

    std::string read_file_to_string(const std::string& path) {
        std::ifstream infile{path};
        std::string contents{std::istreambuf_iterator<char>(infile),
                             std::istreambuf_iterator<char>()};
        return contents;
    }

    std::filesystem::path get_module_directory(HMODULE h_module) {
        wchar_t path[MAX_PATH];

        if (GetModuleFileNameW(h_module, path, MAX_PATH) == 0) {
            return "";
        }

        return std::filesystem::path(path).parent_path();
    }

    std::optional<std::filesystem::path> find_game_directory() {
        auto current_dir = get_module_directory(nullptr);
        if (std::filesystem::exists(current_dir / "rfg.exe")) {
            return current_dir;
        }

        auto parent_dir = current_dir.parent_path();
        if (std::filesystem::exists(parent_dir / "rfg.exe")) {
            return parent_dir;
        }

        return std::nullopt;
    }

    std::optional<std::filesystem::path> find_sledge_directory() {
        auto current_dir = get_module_directory(nullptr);
        if (std::filesystem::exists(current_dir / "sledge.dll") &&
            std::filesystem::exists(current_dir / "launcher.exe")) {
            return current_dir;
        }

        auto sledge_subdir = current_dir / "sledge";
        if (std::filesystem::exists(sledge_subdir / "sledge.dll") &&
            std::filesystem::exists(sledge_subdir / "launcher.exe")) {
            return sledge_subdir;
        }

        return std::nullopt;
    }

    std::optional<std::filesystem::path> open_folder_dialog() {
        std::optional<std::filesystem::path> directory;

        NFD_Init();
        nfdu8char_t* outPath;
        nfdresult_t result = NFD_PickFolderU8(&outPath, "");
        if (result == NFD_OKAY) {
            directory = outPath;
            NFD_FreePathU8(outPath);
        } else if (result != NFD_CANCEL) {
            spdlog::error("Failed picking folder in dialog: {}", NFD_GetError());
        }
        NFD_Quit();

        return directory;
    }

    std::string key_to_string(key key) { return std::string(magic_enum::enum_name(key)); }

    key key_from_string(const std::string& string) {
        return magic_enum::enum_cast<key>(string).value_or(key::none);
    }
}
