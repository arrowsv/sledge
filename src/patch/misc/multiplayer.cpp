#include "multiplayer.hpp"

#include "common/constants.hpp"
#include "common/mods.hpp"
#include "common/utils/os.hpp"
#include "patch/main.hpp"
#include "patch/rfg/math/hash.hpp"
#include "patch/utils/hook.hpp"
#include "patch/utils/memory.hpp"

#include <filesystem>
#include <fstream>
#include <spdlog/spdlog.h>

namespace {
    void set_hash() {
        uint32_t misc_hash = 0;
        std::filesystem::path misc_file(utils::os::get_module_directory(g_game_module_base) /
                                        "data" / "misc.vpp_pc");
        std::ifstream file(misc_file, std::ios::binary | std::ios::ate);
        if (file.is_open()) {
            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> file_buffer(size);
            if (file.read(file_buffer.data(), size)) {
                misc_hash =
                    rfg::get_crc32_from_buffer(file_buffer.data(), static_cast<uint32_t>(size));
            }
            file.close();
        }

        size_t num_enabled_mods = mods::manager::get().get_enabled_mods().size();

        auto data_str = std::format("{}|{}|{}", constants::version, misc_hash, num_enabled_mods);
        uint32_t new_hash = rfg::get_crc32_from_string(data_str.c_str());

        spdlog::debug("Calculated multiplayer hash: '{}'", new_hash);
        *rfg::g_mod_table_hash() = new_hash;
    }
}

namespace misc::multiplayer {
    HOOK_FUNC(OFFSET(0x008ab7a0, 0x008ab7a0), void, __cdecl, multi_init_job) {
        set_hash();
        multi_init_job_original();
    }

    void apply_patches() {
        // Remove "Matchmaking" menu option
        utils::memory::write_value<uint8_t>(OFFSET(0x16624B0, 0x016634b0), 0);

        // Remove "Spectator" menu option
        utils::memory::write_value<uint8_t>(OFFSET(0x16624F0, 0x016634f0), 0);

        multi_init_job_apply();
    }
}