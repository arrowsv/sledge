#include "injector.hpp"
#include "common/utils/os.hpp"

#include <libloaderapi.h>
#include <plog/Log.h>

namespace injector
{
bool inject_dll(const std::filesystem::path &dll_file, const HANDLE &process)
{
    size_t dll_path_size = dll_file.string().length() + 1;

    LPVOID remote_path_memory = VirtualAllocEx(process, NULL, dll_path_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (!remote_path_memory)
        return false;

    if (!WriteProcessMemory(process, remote_path_memory, dll_file.string().c_str(), dll_path_size, NULL))
    {
        return false;
    }

    PTHREAD_START_ROUTINE load_library =
        (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
    HANDLE load_thread = CreateRemoteThread(process, NULL, 0, load_library, remote_path_memory, 0, NULL);
    if (!load_thread)
        return false;

    WaitForSingleObject(load_thread, INFINITE);
    DWORD remote_dll_base = 0;
    GetExitCodeThread(load_thread, (LPDWORD)&remote_dll_base);
    CloseHandle(load_thread);

    if (remote_dll_base == 0)
        return false;

    HMODULE local_dll = LoadLibraryA(dll_file.string().c_str());
    if (!local_dll)
        return false;

    FARPROC local_initialize = GetProcAddress(local_dll, "initialize");
    if (!local_initialize)
    {
        FreeLibrary(local_dll);
        return false;
    }

    ptrdiff_t offset = (BYTE *)local_initialize - (BYTE *)local_dll;
    FreeLibrary(local_dll);

    LPTHREAD_START_ROUTINE remote_initialize = (LPTHREAD_START_ROUTINE)((BYTE *)remote_dll_base + offset);

    HANDLE init_thread = CreateRemoteThread(process, NULL, 0, remote_initialize, NULL, 0, NULL);
    if (!init_thread)
        return false;

    WaitForSingleObject(init_thread, INFINITE);
    DWORD exit_code = 0;
    GetExitCodeThread(init_thread, &exit_code);
    CloseHandle(init_thread);

    return exit_code == TRUE;
}

bool run_game(const std::filesystem::path &game_directory, bool vanilla)
{
    auto game_file = game_directory / "rfg.exe";

    auto sledge_directory = utils::os::get_module_directory(GetModuleHandleA(nullptr));
    auto dll_file = sledge_directory / "sledge.dll";

    STARTUPINFOA startup_info{sizeof(startup_info)};
    PROCESS_INFORMATION process_info{0};

    if (!CreateProcessA(game_file.string().c_str(), nullptr, nullptr, nullptr, FALSE, CREATE_SUSPENDED, NULL,
                        game_directory.string().c_str(), &startup_info, &process_info))
    {
        utils::os::show_message_error("Failed to create process.");
        return false;
    }

    if (!vanilla && !inject_dll(dll_file, process_info.hProcess))
    {
        utils::os::show_message_error("Failed to inject or initialize 'sledge.dll'.");
        TerminateProcess(process_info.hProcess, 0);
        return false;
    }

    ResumeThread(process_info.hThread);

    // if (config::get().keep_launcher_open)
    //     WaitForSingleObject(process_info.hProcess, INFINITE);

    CloseHandle(process_info.hProcess);
    CloseHandle(process_info.hThread);
    return true;
}

} // namespace injector
