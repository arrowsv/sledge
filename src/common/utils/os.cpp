#include "os.hpp"
#include "plog/Log.h"

#include <fstream>
#include <windows.h>
#include <nfd.h>
#include <magic_enum.hpp>

namespace utils::os {

void show_message_info(const std::string& message) {
    PLOG_INFO << message;
    MessageBoxA(NULL, message.c_str(), "Sledge", MB_OK | MB_ICONINFORMATION);
}

void show_message_error(const std::string& message) {
    PLOG_ERROR << message;
    MessageBoxA(NULL, message.c_str(), "Sledge", MB_OK | MB_ICONERROR);
}

std::string read_file_to_string(const std::string& path) {
    std::ifstream infile{path};
    std::string contents{std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};
    return contents;
}

std::filesystem::path get_module_directory(HMODULE h_module) {
    wchar_t path[MAX_PATH];

    if (GetModuleFileNameW(h_module, path, MAX_PATH) == 0) {
        return "";
    }

    return std::filesystem::path(path).parent_path();
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
        PLOG_ERROR << "Error in file dialog: " << NFD_GetError();
    }
    NFD_Quit();

    return directory;
}

std::string key_to_string(key key) { return std::string(magic_enum::enum_name(key)); }

key key_from_string(const std::string& string) {
    return magic_enum::enum_cast<key>(string).value_or(key::none);
}
} // namespace utils::os
