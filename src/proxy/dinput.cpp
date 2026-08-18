#include "launcher/launcher.hpp"
#include <string>
#include <windows.h>

HMODULE g_real_dinput8 = nullptr;
HMODULE g_sledge = nullptr;
bool g_sledge_initialized = false;

using direct_input8_create_t = HRESULT(WINAPI*)(HINSTANCE, DWORD, REFIID, LPVOID*, LPUNKNOWN);
using dll_can_unload_now_t = HRESULT(WINAPI*)();
using dll_get_class_object_t = HRESULT(WINAPI*)(REFCLSID, REFIID, LPVOID*);
using dll_register_server_t = HRESULT(WINAPI*)();
using dll_unregister_server_t = HRESULT(WINAPI*)();
using sledge_initialize_t = bool (*)();

direct_input8_create_t p_direct_input8_create = nullptr;
dll_can_unload_now_t p_dll_can_unload_now = nullptr;
dll_get_class_object_t p_dll_get_class_object = nullptr;
dll_register_server_t p_dll_register_server = nullptr;
dll_unregister_server_t p_dll_unregister_server = nullptr;
sledge_initialize_t p_sledge_initialize = nullptr;
HHOOK p_cbt_hook = nullptr;

template <typename fn_t> bool resolve(HMODULE h_mod, fn_t& fn_out, const char* sz_name) {
    fn_out = reinterpret_cast<fn_t>(GetProcAddress(h_mod, sz_name));
    return fn_out != nullptr;
}

std::wstring get_game_directory() {
    wchar_t sz_path[MAX_PATH]{};
    GetModuleFileNameW(nullptr, sz_path, MAX_PATH);
    std::wstring s_path = sz_path;
    size_t pos = s_path.find_last_of(L"\\/");
    return (pos != std::wstring::npos) ? s_path.substr(0, pos + 1) : L"";
}

void ensure_sledge_loaded() {
    if (g_sledge_initialized)
        return;

    g_sledge_initialized = true;

    std::wstring s_sledge_path = get_game_directory() + L"sledge.dll";
    g_sledge = LoadLibraryW(s_sledge_path.c_str());
    if (!g_sledge)
        return;

    if (!resolve(g_sledge, p_sledge_initialize, "initialize"))
        return;

    p_sledge_initialize();
}

LRESULT CALLBACK cbt_hook_proc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HCBT_CREATEWND) {
        HWND hwnd = reinterpret_cast<HWND>(wParam);
        auto* create_struct = reinterpret_cast<CBT_CREATEWND*>(lParam)->lpcs;

        if ((create_struct->style & WS_CHILD) == 0) {
            create_struct->style &= ~WS_VISIBLE;

            UnhookWindowsHookEx(p_cbt_hook);
            p_cbt_hook = nullptr;

            auto choice = launcher::run();

            if (choice == launcher::choice::quit) {
                std::exit(0);
            }

            if (choice == launcher::choice::play) {
                ensure_sledge_loaded();
            }

            create_struct->style |= WS_VISIBLE;
            ShowWindow(hwnd, SW_SHOW);
            UpdateWindow(hwnd);

            SetForegroundWindow(hwnd);
            SetFocus(hwnd);
            BringWindowToTop(hwnd);
        }
    }
    return CallNextHookEx(p_cbt_hook, nCode, wParam, lParam);
}

bool initialize() {
    wchar_t sz_system_dir[MAX_PATH]{};
    if (!GetSystemDirectoryW(sz_system_dir, MAX_PATH))
        return false;

    std::wstring s_sys_path = sz_system_dir;
    s_sys_path += L"\\dinput8.dll";

    g_real_dinput8 = LoadLibraryW(s_sys_path.c_str());
    if (!g_real_dinput8)
        return false;

    bool b_ok = true;
    b_ok &= resolve(g_real_dinput8, p_direct_input8_create, "DirectInput8Create");
    b_ok &= resolve(g_real_dinput8, p_dll_can_unload_now, "DllCanUnloadNow");
    b_ok &= resolve(g_real_dinput8, p_dll_get_class_object, "DllGetClassObject");
    b_ok &= resolve(g_real_dinput8, p_dll_register_server, "DllRegisterServer");
    b_ok &= resolve(g_real_dinput8, p_dll_unregister_server, "DllUnregisterServer");

    p_cbt_hook = SetWindowsHookExW(WH_CBT, cbt_hook_proc, nullptr, GetCurrentThreadId());

    return b_ok;
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason_for_call, LPVOID reserved) {
    if (reason_for_call == DLL_PROCESS_ATTACH) {
        if (!initialize())
            return FALSE;
    }
    return TRUE;
}

extern "C" {
HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dw_version, REFIID riidltf,
                                  LPVOID* ppv_out, LPUNKNOWN punk_outer) {
    // ensure_sledge_loaded();
    return p_direct_input8_create(hinst, dw_version, riidltf, ppv_out, punk_outer);
}

HRESULT WINAPI DllCanUnloadNow() { return p_dll_can_unload_now(); }

HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) {
    return p_dll_get_class_object(rclsid, riid, ppv);
}

HRESULT WINAPI DllRegisterServer() { return p_dll_register_server(); }

HRESULT WINAPI DllUnregisterServer() { return p_dll_unregister_server(); }
}