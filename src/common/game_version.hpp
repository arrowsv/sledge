#pragma once

#include <filesystem>

enum game_version { unknown, gog, steam };

extern game_version g_game_version;
void identify_game_version(const std::filesystem::path& executable);