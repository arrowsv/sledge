#include "files.hpp"

#include "patch/rfg/os/file.hpp"
#include "patch/utils/hook.hpp"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <spdlog/spdlog.h>
#include <sol/sol.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <pugixml.hpp>

namespace {
    struct memory_entry {
        std::vector<char> buffer;
        rfg::v_packfile parent_packfile{};
        rfg::v_packfile_entry entry{};

        explicit memory_entry(std::vector<char> data) : buffer(std::move(data)) {
            std::memset(&parent_packfile, 0, sizeof(parent_packfile));

            // Reference:
            // cf_open_memory(
            // &vpe->parent->data[2048 * vpe->sector
            //                     - 2048
            //                     + -2048 * ((vpe->parent->filename_size + 2047) >> 11)
            //                     + -2048 * ((vpe->parent->dir_size + 2047) >> 11)],
            //  vpe->size,
            //  (const char *)(vpe->parent->flags & 1),
            //  vpe->compressed_size,
            //  a3);

            parent_packfile.data = buffer.data();
            parent_packfile.filename_size = 0;
            parent_packfile.dir_size = 0;
            parent_packfile.flags = 0;

            std::memset(&entry, 0, sizeof(entry));
            entry.parent = &parent_packfile;
            entry.sector = 1;
            entry.size = static_cast<uint32_t>(buffer.size());
            entry.compressed_size = static_cast<uint32_t>(buffer.size());
        }
    };

    struct vector_xml_writer : pugi::xml_writer {
        std::vector<char>& dest;
        explicit vector_xml_writer(std::vector<char>& out_vec) : dest(out_vec) {}

        virtual void write(const void* data, size_t size) override {
            const char* bytes = static_cast<const char*>(data);
            dest.insert(dest.end(), bytes, bytes + size);
        }
    };

    std::unordered_map<std::string, std::filesystem::path> source_file_registry;
    std::unordered_map<std::string, std::unique_ptr<memory_entry>> memory_entry_registry;
    std::unordered_map<std::string, std::vector<sol::protected_function>> xml_edit_registry;
    std::unordered_set<std::filesystem::path> packfile_registry;
    
    const std::unordered_set<std::string> valid_xml_exts = {".xtbl", ".dtodx", ".gtodx"};

    bool extract_game_file(const std::string& file_name, std::vector<char>& out_buffer) {
        rfg::cfile* file = rfg::cf_open_file_name(file_name.c_str(), "rb", rfg::PLATFORM_PC, false);
        if (!file) {
            spdlog::error("Failed to open game file '{}' for extraction.", file_name);
            return false;
        }

        uint32_t size = file->size;
        if (!size) {
            spdlog::error("Failed to read size of extracted game file '{}'.", file_name);
            rfg::cf_close(file);
            return false;
        }

        out_buffer.resize(size);
        rfg::cf_read(out_buffer.data(), size, file, false);
        rfg::cf_close(file);
        return true;
    }

    void process_and_stage_files() {
        for (const auto& [file_name, source_path] : source_file_registry) {
            std::ifstream file(source_path, std::ios::binary | std::ios::ate);
            if (!file.is_open()) {
                spdlog::error("Failed to open registered file '{}'.",
                              source_path.string());
                continue;
            }

            std::streamsize size = file.tellg();
            file.seekg(0, std::ios::beg);

            std::vector<char> buffer(size);
            if (file.read(buffer.data(), size)) {
                memory_entry_registry[file_name] =
                    std::make_unique<memory_entry>(std::move(buffer));
            }
        }

        for (const auto& [file_name, modifiers] : xml_edit_registry) {
            std::vector<char> raw_buffer;

            auto it = memory_entry_registry.find(file_name);
            if (it != memory_entry_registry.end()) {
                raw_buffer = it->second->buffer;
            } else {
                if (!extract_game_file(file_name, raw_buffer)) {
                    spdlog::error("Skipping XML edits for '{}': extraction failed.", file_name);
                    continue;
                }
            }

            pugi::xml_document doc;
            pugi::xml_parse_result parse_res =
                doc.load_buffer(raw_buffer.data(), raw_buffer.size());
            if (!parse_res) {
                spdlog::error("Failed to parse XML for '{}': {}", file_name,
                              parse_res.description());
                continue;
            }

            for (const auto& modify_func : modifiers) {
                auto res = modify_func(&doc);
                if (!res.valid()) {
                    sol::error err = res;
                    spdlog::error("Lua XML modification error on '{}': {}", file_name, err.what());
                }
            }

            std::vector<char> modified_buffer;
            vector_xml_writer writer(modified_buffer);
            doc.save(writer, "  ", pugi::format_default | pugi::format_no_declaration);

            memory_entry_registry[file_name] =
                std::make_unique<memory_entry>(std::move(modified_buffer));
        }
    }
}

namespace misc::files {
    void register_file(const std::filesystem::path& file_path) {
        if (!std::filesystem::exists(file_path)) {
            spdlog::error("Failed to register file '{}': file does not exist.", file_path.string());
            return;
        }

        std::string file_name = file_path.filename().string();
        source_file_registry[file_name] = file_path;
    }

    void register_packfile(const std::filesystem::path& file_path) {
        if (packfile_registry.contains(file_path)) {
            spdlog::warn("Skipped registering packfile '{}': packfile is already registered.",
                         file_path.string());
            return;
        }

        if (!std::filesystem::exists(file_path)) {
            spdlog::error("Failed to register packfile '{}': file does not exist.",
                          file_path.string());
            return;
        }
        packfile_registry.insert(file_path);
    }

    void register_xml_edit(const std::string& file_name, sol::protected_function modify_function) {
        std::filesystem::path file_path(file_name);

        if (file_name.empty() || !file_path.has_extension()) {
            spdlog::error("Failed to register XML edit for '{}': file name is not valid.", file_name);
            return;
        }

        std::string ext = file_path.extension().string();
        if (!valid_xml_exts.contains(ext)) {
            spdlog::error("Failed to register XML edit for '{}': '{}' is not a supported file type.", file_name, ext);
            return;
        }

        xml_edit_registry[file_name].push_back(modify_function);
    }

    HOOK_FUNC(OFFSET(0x005d4780, 0x005d4860), void, __cdecl, game_enable_table_precache) { return; }

    HOOK_FUNC(OFFSET(0x005c20f0, 0x005c21e0), bool, __cdecl, cf_find_file,
              rfg::cf_found_info* found_info, const char* file_name, bool encrypted) {
        std::filesystem::path path(file_name);
        std::string filename_str = path.filename().string();

        auto it = memory_entry_registry.find(filename_str);
        if (it == memory_entry_registry.end()) {
            return cf_find_file_original(found_info, file_name, encrypted);
        }

        memory_entry* mem_entry = it->second.get();

        std::strncpy(found_info->full_name, filename_str.c_str(),
                     sizeof(found_info->full_name) - 1);
        found_info->full_name[sizeof(found_info->full_name) - 1] = '\0';
        found_info->size = static_cast<uint32_t>(mem_entry->buffer.size());
        found_info->searched_system = rfg::CF_SEARCH_PACKFILE;
        found_info->media_type = rfg::CF_IO_MEDIA_MEMORY;
        found_info->vpe = &mem_entry->entry;

        return true;
    }

    HOOK_FUNC(OFFSET(0x005d4d10, 0x005d4df0), bool, __cdecl, init_packfiles) {
        bool result = init_packfiles_original();
        if (result) {
            rfg::game_enable_standard_access();
            for (auto packfile : packfile_registry) {
                auto vpp_result =
                    rfg::packfile_add(packfile.string().c_str(), nullptr, false, false);
                if (!vpp_result) {
                    spdlog::error("Failed to add packfile '{}'.", packfile.string());
                }
            }
            process_and_stage_files();
            rfg::game_disable_standard_access();
        }
        return result;
    }

    void apply_patches() {
        cf_find_file_apply();
        game_enable_table_precache_apply();
        init_packfiles_apply();
    }
}