#include "wnd_proc.hpp"

#include "input.hpp"
#include "common/config.hpp"
#include "patch/graphics/graphics.hpp"
#include "patch/gui/manager.hpp"

#include <windows.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM w_param,
                                                             LPARAM l_param);
namespace input {
    WNDPROC g_original_wnd_proc = nullptr;

    static bool is_mouse_message(UINT msg) {
        return (msg >= WM_MOUSEFIRST && msg <= WM_MOUSELAST) || msg == WM_SETCURSOR;
    }

    static bool is_key_message(UINT msg) {
        return (msg >= WM_KEYFIRST && msg <= WM_KEYLAST) || msg == WM_CHAR || msg == WM_UNICHAR;
    }

    LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
        if (graphics::is_imgui_initialized()) {
            auto& gui_manager = gui::manager::get();

            if ((msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN) &&
                w_param == (int)config::get().sledge.overlay_key) {
                gui_manager.g_show_overlay = !gui_manager.g_show_overlay;
                return true;
            }

            ImGui_ImplWin32_WndProcHandler(hwnd, msg, w_param, l_param);

            if (gui_manager.g_show_overlay) {
                const ImGuiIO& io = ImGui::GetIO();

                if (is_mouse_message(msg) && (io.WantCaptureMouse || gui_manager.g_show_overlay)) {
                    return true;
                }

                if (is_key_message(msg) && io.WantCaptureKeyboard) {
                    return true;
                }
            }
        }

        input::process_event_input(hwnd, msg, w_param, l_param);
        return CallWindowProc(g_original_wnd_proc, hwnd, msg, w_param, l_param);
    }
}