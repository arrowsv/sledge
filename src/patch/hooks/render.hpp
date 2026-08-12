#pragma once

#include "common/utils/os.hpp"

namespace hooks::render {
void apply();

bool is_key_down(utils::os::key key);
bool is_key_just_pressed(utils::os::key key);
bool is_key_just_released(utils::os::key key);
} // namespace hooks::render
