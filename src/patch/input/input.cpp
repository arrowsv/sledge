#include "input.hpp"

#include "patch/graphics/graphics.hpp"
#include "patch/gui/manager.hpp"
#include "patch/lua/manager.hpp"
#include "patch/lua/events/input.hpp"
#include "patch/utils/hook.hpp"

namespace {
    constexpr uint32_t key_count = 256;
    std::array<bool, key_count> key_states{};
    std::array<bool, key_count> key_states_prev{};
}

namespace input {
    bool should_block_game_input() {
        return graphics::is_imgui_initialized() && gui::manager::get().is_input_required();
    }

    void poll_key_states() { key_states_prev = key_states; }

    void set_key_state(WPARAM vk_code, bool down) {
        if (vk_code < key_count)
            key_states[vk_code] = down;
    }

    bool is_key_down(utils::os::key key) {
        if ((int)key < 0 || (int)key >= (int)key_count)
            return false;
        return key_states[(int)key];
    }

    bool is_key_just_pressed(utils::os::key key) {
        if ((int)key < 0 || (int)key >= (int)key_count)
            return false;
        return key_states[(int)key] && !key_states_prev[(int)key];
    }

    bool is_key_just_released(utils::os::key key) {
        if ((int)key < 0 || (int)key >= (int)key_count)
            return false;
        return !key_states[(int)key] && key_states_prev[(int)key];
    }

    void process_event_input(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
        bool shift_down = key_states[VK_SHIFT];
        bool control_down = key_states[VK_CONTROL];
        bool alt_down = key_states[VK_MENU];

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

                input::set_key_state(vk_code, true);
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

                input::set_key_state(vk_code, false);
                lua::manager::get().trigger_event(
                    lua::events::event::key_up,
                    lua::events::key_up_event(vk_code, shift_down, control_down, alt_down), {});
                break;
            }
            default:
                break;
        }
    }

    HOOK_FUNC(OFFSET(0xC78D80, 0x00c790b0), void, __cdecl, mouse_set_relative_input,
              void* input_system, bool enabled) {
        return mouse_set_relative_input_original(input_system,
                                                 should_block_game_input() ? false : enabled);
    }

    void apply_patches() { mouse_set_relative_input_apply(); }
}