#pragma once

#include <windef.h>

enum game_version { gog, steam };

extern game_version g_game_version;
extern HMODULE g_sledge_module_base;
extern HMODULE g_game_module_base;
extern HWND g_game_window_handle;
