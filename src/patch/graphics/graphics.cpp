#include "graphics.hpp"

#include "common/utils/imgui.hpp"
#include "patch/input/wnd_proc.hpp"
#include "patch/main.hpp"
#include "patch/gui/manager.hpp"
#include "patch/utils/hook.hpp"
#include "patch/rfg/game.hpp"
#include "patch/rfg/graphics.hpp"
#include "patch/input/input.hpp"

#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_dx11.h>

namespace {
    bool imgui_initialized = false;
    rfg::graphics_system* graphics_system = nullptr;
    rfg::render_swap_chain* swap_chain = nullptr;
    ID3D11Device* d3d11_device = nullptr;
    ID3D11DeviceContext* d3d11_device_context = nullptr;
    IDXGISwapChain* d3d11_swap_chain = nullptr;
}

namespace graphics {
    bool ready_to_initialize_imgui() {
        if (!graphics_system || !graphics_system->pDevice || !graphics_system->pImmediateContext ||
            !graphics_system->pDefaultSwapChain ||
            !graphics_system->pDefaultSwapChain->pSwapChain ||
            !graphics_system->pDefaultSwapChain->pBackBufferRenderTargetView)
            return false;

        rfg::game_state state = rfg::gameseq_get_state();
        if (state < 0 || state > 63)
            return false;

        if (!g_game_window_handle) {
            if (!swap_chain || !swap_chain->windowHandle)
                return false;

            g_game_window_handle = swap_chain->windowHandle;
        }

        return true;
    }

    void initialize_imgui() {
        utils::imgui::initialize();

        ImGui_ImplDX11_Init(d3d11_device, d3d11_device_context);
        ImGui_ImplWin32_Init(g_game_window_handle);

        input::g_original_wnd_proc = (WNDPROC)SetWindowLongPtr(g_game_window_handle, GWLP_WNDPROC,
                                                               (LONG_PTR)input::wnd_proc);

        imgui_initialized = true;
    }

    HOOK_FUNC(OFFSET(0xC6A8A0, 0x00c6abd0), void*, __cdecl, keen_graphics_begin_frame,
              rfg::graphics_system* p_graphics_system, rfg::render_swap_chain* p_swap_chain) {
        if (graphics_system != p_graphics_system || swap_chain != p_swap_chain) {
            graphics_system = p_graphics_system;
            swap_chain = p_swap_chain;
        }

        input::poll_key_states();

        if (imgui_initialized)
            return keen_graphics_begin_frame_original(p_graphics_system, p_swap_chain);

        if (!ready_to_initialize_imgui())
            return keen_graphics_begin_frame_original(p_graphics_system, p_swap_chain);

        d3d11_device = graphics_system->pDevice;
        d3d11_device_context = graphics_system->pImmediateContext;
        d3d11_swap_chain = graphics_system->pDefaultSwapChain->pSwapChain;

        initialize_imgui();

        return keen_graphics_begin_frame_original(p_graphics_system, p_swap_chain);
    }

    HOOK_FUNC(OFFSET(0xC6FFF0, 0x00c70320), bool, __cdecl, keen_graphics_end_frame,
              rfg::graphics_system* p_graphics_system) {
        if (!imgui_initialized)
            return keen_graphics_end_frame_original(p_graphics_system);

        if (!p_graphics_system->pCurrentSwapChain ||
            !p_graphics_system->pCurrentSwapChain->backBufferRenderTarget.renderTargetViews[0])
            return keen_graphics_end_frame_original(p_graphics_system);

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        gui::manager::get().draw();

        if (gui::manager::get().g_show_overlay) {
            *rfg::g_mouse_visible() = true;
        }

        d3d11_device_context->OMSetRenderTargets(
            1, &graphics_system->pCurrentSwapChain->backBufferRenderTarget.renderTargetViews[0],
            nullptr);
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        return keen_graphics_end_frame_original(p_graphics_system);
    }

    bool is_imgui_initialized() { return imgui_initialized; }

    void apply_patches() {
        keen_graphics_begin_frame_apply();
        keen_graphics_end_frame_apply();
    }
}