#pragma once

#include <filesystem>
#include <windows.h>

namespace injector {
bool run_game(const std::filesystem::path& game_executable, bool vanilla = false);
}; // namespace injector
