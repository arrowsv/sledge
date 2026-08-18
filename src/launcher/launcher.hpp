#pragma once

namespace launcher {
enum class choice { play, play_vanilla, quit };
choice run();
void select_play();
void select_play_vanilla();
} // namespace launcher