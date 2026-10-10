#pragma once

#include <semver.hpp>

using namespace semver::literals;

namespace constants {
    inline constexpr auto sledge_version = semver::version(0, 3, 0);
    inline constexpr auto api_version = semver::version(1, 0, 0);
}