#include "common/utils/os.hpp"

#include <filesystem>
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

template <typename fn_t> bool resolve(HMODULE h_mod, fn_t& fn_out, const char* sz_name) {
    fn_out = reinterpret_cast<fn_t>(GetProcAddress(h_mod, sz_name));
    return fn_out != nullptr;
}

bool launch_in_vanilla() {
    auto found_sledge_dir = utils::os::find_sledge_directory();
    if (found_sledge_dir) {
        auto vanilla_file = found_sledge_dir.value() / "sledge_launch_vanilla.txt";
        if (std::filesystem::exists(vanilla_file)) {
            try {
                std::filesystem::remove(vanilla_file);
            } catch (const std::filesystem::filesystem_error& e) {
                utils::os::show_message_error(
                    std::format("Error deleting '{}': {}", vanilla_file.string(), e.what()));
            }
            return true;
        }
    }

    int argc;
    wchar_t** argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv) {
        return false;
    }

    bool found = false;
    for (int i = 0; i < argc; ++i) {
        if (std::wcscmp(argv[i], L"--vanilla") == 0) {
            found = true;
            break;
        }
    }
    LocalFree(argv);
    return found;
}

void ensure_sledge_loaded() {
    if (g_sledge_initialized) {
        return;
    }

    g_sledge_initialized = true;

    if (launch_in_vanilla()) {
        return;
    }

    auto found_sledge_dir = utils::os::find_sledge_directory();
    if (!found_sledge_dir) {
        utils::os::show_message_error(
            "Failed to inject Sledge: Sledge directory couldn't be found."
            "\n\nSledge must be placed in the game's root folder or 'sledge' subdirectory.");
        return;
    }
    auto sledge_dll = found_sledge_dir.value() / "sledge.dll";

    g_sledge = LoadLibraryW(sledge_dll.c_str());
    if (!g_sledge) {
        return;
    }

    if (!resolve(g_sledge, p_sledge_initialize, "initialize")) {
        return;
    }

    p_sledge_initialize();
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
        ensure_sledge_loaded();
        return p_direct_input8_create(hinst, dw_version, riidltf, ppv_out, punk_outer);
    }

    HRESULT WINAPI DllCanUnloadNow() { return p_dll_can_unload_now(); }

    HRESULT WINAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) {
        return p_dll_get_class_object(rclsid, riid, ppv);
    }

    HRESULT WINAPI DllRegisterServer() { return p_dll_register_server(); }

    HRESULT WINAPI DllUnregisterServer() { return p_dll_unregister_server(); }
}