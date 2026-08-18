#include "render.hpp"

#include "common/config.hpp"
#include "common/utils/imgui.hpp"
#include "patch/gui/gui.hpp"
#include "patch/lua/events/input.hpp"
#include "patch/lua/manager.hpp"
#include "patch/main.hpp"
#include "patch/rfg/game.hpp"
#include "patch/rfg/graphics.hpp"
#include "patch/utils/hook.hpp"

#include <array>
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <imgui.h>
#include <windows.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM w_param,
                                                             LPARAM l_param);

namespace hooks::render {
rfg::graphics_system* g_graphics_system = nullptr;
rfg::render_swap_chain* g_swap_chain = nullptr;
ID3D11Device* g_d3d11_device = nullptr;
ID3D11DeviceContext* g_d3d11_device_context = nullptr;
IDXGISwapChain* g_d3d11_swap_chain = nullptr;
WNDPROC g_original_wnd_proc = nullptr;
LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);

bool g_imgui_initialized = false;

constexpr uint32_t key_count = 256;
std::array<bool, key_count> g_key_states{};
std::array<bool, key_count> g_key_states_prev{};

static bool should_block_game_input() {
    return g_imgui_initialized && gui::manager::get().g_show_windows;
}

void poll_key_states() {
    g_key_states_prev = g_key_states;

    bool window_focused = GetForegroundWindow() == g_game_window_handle;
    bool imgui_wants_keyboard = g_imgui_initialized && ImGui::GetIO().WantCaptureKeyboard &&
                                gui::manager::get().g_show_windows;

    for (size_t vk = 0; vk < key_count; vk++)
        g_key_states[vk] =
            window_focused && !imgui_wants_keyboard && (GetAsyncKeyState((int)vk) & 0x8000) != 0;
}

bool is_key_down(utils::os::key key) {
    if ((int)key < 0 || (int)key >= (int)key_count)
        return false;
    return g_key_states[(int)key];
}

bool is_key_just_pressed(utils::os::key key) {
    if ((int)key < 0 || (int)key >= (int)key_count)
        return false;
    return g_key_states[(int)key] && !g_key_states_prev[(int)key];
}

bool is_key_just_released(utils::os::key key) {
    if ((int)key < 0 || (int)key >= (int)key_count)
        return false;
    return !g_key_states[(int)key] && g_key_states_prev[(int)key];
}

void process_event_input(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
    bool shift_down = g_key_states[VK_SHIFT];
    bool control_down = g_key_states[VK_CONTROL];
    bool alt_down = g_key_states[VK_MENU];

    switch (msg) {
    case WM_MOUSEWHEEL:
        lua::manager::get().trigger_event(
            lua::events::event::mouse_wheel,
            lua::events::mouse_wheel_event(GET_WHEEL_DELTA_WPARAM(w_param), shift_down,
                                           control_down, alt_down),
            {});
        break;

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN: {
        WPARAM vk_code = w_param;
        if (msg == WM_LBUTTONDOWN)
            vk_code = VK_LBUTTON;
        else if (msg == WM_RBUTTONDOWN)
            vk_code = VK_RBUTTON;
        else if (msg == WM_MBUTTONDOWN)
            vk_code = VK_MBUTTON;
        lua::manager::get().trigger_event(
            lua::events::event::key_down,
            lua::events::key_down_event(vk_code, shift_down, control_down, alt_down), {});
        break;
    }

    case WM_KEYUP:
    case WM_SYSKEYUP:
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP: {
        WPARAM vk_code = w_param;

        if (msg == WM_LBUTTONUP)
            vk_code = VK_LBUTTON;
        else if (msg == WM_RBUTTONUP)
            vk_code = VK_RBUTTON;
        else if (msg == WM_MBUTTONUP)
            vk_code = VK_MBUTTON;

        lua::manager::get().trigger_event(
            lua::events::event::key_up,
            lua::events::key_up_event(vk_code, shift_down, control_down, alt_down), {});
        break;
    }
    default:
        break;
    }
}

bool ready_to_initialize_imgui() {
    if (!g_graphics_system || !g_graphics_system->pDevice ||
        !g_graphics_system->pImmediateContext || !g_graphics_system->pDefaultSwapChain ||
        !g_graphics_system->pDefaultSwapChain->pSwapChain ||
        !g_graphics_system->pDefaultSwapChain->pBackBufferRenderTargetView)
        return false;

    rfg::game_state state = rfg::gameseq_get_state();
    if (state < 0 || state > 63)
        return false;

    if (!g_game_window_handle) {
        if (!g_swap_chain || !g_swap_chain->windowHandle)
            return false;

        g_game_window_handle = g_swap_chain->windowHandle;
    }

    return true;
}

void initialize_imgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = NULL;
    io.LogFilename = NULL;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui_ImplDX11_Init(g_d3d11_device, g_d3d11_device_context);
    ImGui_ImplWin32_Init(g_game_window_handle);
    g_original_wnd_proc =
        (WNDPROC)SetWindowLongPtr(g_game_window_handle, GWLP_WNDPROC, (LONG_PTR)wnd_proc);

    utils::imgui::initialize_styles();
    utils::imgui::initialize_fonts();

    g_imgui_initialized = true;
}

static bool is_input_message(UINT msg) {
    switch (msg) {
    case WM_MOUSEMOVE:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_LBUTTONDBLCLK:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
    case WM_RBUTTONDBLCLK:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_MBUTTONDBLCLK:
    case WM_XBUTTONDOWN:
    case WM_XBUTTONUP:
    case WM_XBUTTONDBLCLK:
    case WM_MOUSEWHEEL:
    case WM_MOUSEHWHEEL:
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_SYSKEYUP:
    case WM_CHAR:
    case WM_UNICHAR:
    case WM_SETCURSOR:
        return true;
    default:
        return false;
    }
}

LRESULT CALLBACK wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
    if (g_imgui_initialized) {
        auto& gui_manager = gui::manager::get();

        if (msg == WM_KEYDOWN && w_param == (int)config::get().open_key)
            gui_manager.g_show_windows = !gui_manager.g_show_windows;

        if (gui_manager.g_show_windows) {
            LRESULT result = ImGui_ImplWin32_WndProcHandler(hwnd, msg, w_param, l_param);
            if (result && is_input_message(msg))
                return result;
        }
    }

    process_event_input(hwnd, msg, w_param, l_param);

    return CallWindowProc(g_original_wnd_proc, hwnd, msg, w_param, l_param);
}

HOOK_FUNC(OFFSET(0x59A180, 0x0059a290), void, __cdecl, key_poll) {
    if (should_block_game_input())
        return;
    return key_poll_original();
}

HOOK_FUNC(OFFSET(0x5C3570, 0x005c3660), void, __cdecl, mouse_poll) {
    if (should_block_game_input())
        return;
    return mouse_poll_original();
}

HOOK_FUNC(OFFSET(0xC78D80, 0x00c790b0), void, __cdecl, mouse_set_relative_input, void* input_system, bool enabled) {
    return mouse_set_relative_input_original(input_system,
                                             should_block_game_input() ? false : enabled);
}

HOOK_FUNC(OFFSET(0xC6A8A0, 0x00c6abd0), void*, __cdecl, keen_graphics_begin_frame,
          rfg::graphics_system* p_graphics_system, rfg::render_swap_chain* p_swap_chain) {
    if (g_graphics_system != p_graphics_system || g_swap_chain != p_swap_chain) {
        g_graphics_system = p_graphics_system;
        g_swap_chain = p_swap_chain;
    }

    poll_key_states();

    if (g_imgui_initialized)
        return keen_graphics_begin_frame_original(p_graphics_system, p_swap_chain);

    if (!ready_to_initialize_imgui())
        return keen_graphics_begin_frame_original(p_graphics_system, p_swap_chain);

    g_d3d11_device = g_graphics_system->pDevice;
    g_d3d11_device_context = g_graphics_system->pImmediateContext;
    g_d3d11_swap_chain = g_graphics_system->pDefaultSwapChain->pSwapChain;

    initialize_imgui();

    return keen_graphics_begin_frame_original(p_graphics_system, p_swap_chain);
}

HOOK_FUNC(OFFSET(0xC6FFF0, 0x00c70320), bool, __cdecl, keen_graphics_end_frame,
          rfg::graphics_system* p_graphics_system) {
    if (!g_imgui_initialized)
        return keen_graphics_end_frame_original(p_graphics_system);

    if (!p_graphics_system->pCurrentSwapChain ||
        !p_graphics_system->pCurrentSwapChain->backBufferRenderTarget.renderTargetViews[0])
        return keen_graphics_end_frame_original(p_graphics_system);

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    ImGuiIO& io = ImGui::GetIO();
    gui::manager::get().draw();
    io.MouseDrawCursor = gui::manager::get().g_show_windows;

    g_d3d11_device_context->OMSetRenderTargets(
        1, &g_graphics_system->pCurrentSwapChain->backBufferRenderTarget.renderTargetViews[0],
        nullptr);
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return keen_graphics_end_frame_original(p_graphics_system);
}

void apply() {
    keen_graphics_begin_frame_apply();
    keen_graphics_end_frame_apply();

    // Disable input when overlays are open
    key_poll_apply();
    mouse_poll_apply();
    mouse_set_relative_input_apply();
}
} // namespace hooks::render
