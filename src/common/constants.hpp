#pragma once

#include <semver.hpp>
#include <string>

using namespace semver::literals;

namespace constants {
    inline constexpr auto sledge_version = semver::version(0, 4, 0);
    inline constexpr auto api_version = semver::version(1, 1, 0);

    inline std::string format_version() {
        return std::format("Sledge {} (API {})", sledge_version.to_string(), api_version.to_string());
    }
}