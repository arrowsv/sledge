#include "game_version.hpp"

#include "utils/os.hpp"

#include <picosha2.h>
#include <array>
#include <string>
#include <vector>
#include <fstream>

namespace {
    struct hash_version {
        std::string_view hash;
        game_version version;
    };

    constexpr std::array version_hashes = {
        // 1.0_Fix - 2025-01-30
        // cs:4931 - 2018-09-20
        hash_version{"7a82d2d0f425af5e75d8ffbce12fac53eb5ca9cd812731ccf5a29697e906af0e",
                     game_version::gog},

        // 10642344 - 2023-02-26
        // 3121288 - 2018-09-20
        hash_version{"0d52039e7f2d3f25a4be52a2aba83919456fb3f00e52e75051726247471a2df4",
                     game_version::steam}};
}

game_version g_game_version;

void identify_game_version(const std::filesystem::path& executable) {
    std::ifstream file(executable, std::ios::binary);
    if (!file.is_open()) {
        utils::os::show_message_error("Failed to open rfg.exe to identify game version.");
        g_game_version = game_version::unknown;
        return;
    }

    std::vector<unsigned char> hash(picosha2::k_digest_size);
    picosha2::hash256(file, hash.begin(), hash.end());
    std::string file_hash = picosha2::bytes_to_hex_string(hash.begin(), hash.end());

    auto it = std::find_if(version_hashes.begin(), version_hashes.end(),
                           [&file_hash](const auto& item) { return item.hash == file_hash; });

    if (it != version_hashes.end()) {
        g_game_version = it->version;
        return;
    }

    utils::os::show_message_error("Unknown game version detected.\nHash: \'" + file_hash + "\'.");
    g_game_version = game_version::unknown;
}