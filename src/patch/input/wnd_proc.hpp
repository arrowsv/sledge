#pragma once

#include <windows.h>

namespace input {
extern WNDPROC g_original_wnd_proc;
LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
}
