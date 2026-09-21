#pragma once

#include "common/utils/os.hpp"

namespace input {
bool should_block_game_input();
void poll_key_states();

bool is_key_down(utils::os::key key);
bool is_key_just_pressed(utils::os::key key);
bool is_key_just_released(utils::os::key key);

void process_event_input(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
void apply_patches();
}