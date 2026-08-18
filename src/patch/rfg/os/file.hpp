#pragma once

#include "patch/rfg/containers.hpp"
#include "patch/utils/memory.hpp"

namespace rfg {
union cfile_union {
    void* m_standard_fp;
    void* m_packfile_fp;
    void* _m_memory_fp;
};

enum cf_search_types {
    CF_SEARCH_NONE = 0xFFFFFFFF,
    CF_SEARCH_STANDARD = 0x0,
    CF_SEARCH_PACKFILE = 0x1,
    CF_SEARCH_VDIR = 0x2,
    CF_SEARCH_NUM_TYPES = 0x3,
};

enum cf_io_media_types {
    CF_IO_MEDIA_NONE = 0xFFFFFFFF,
    CF_IO_MEDIA_HDD = 0x0,
    CF_IO_MEDIA_DVD = 0x1,
    CF_IO_MEDIA_HOST = 0x2,
    CF_IO_MEDIA_MEMORY = 0x5,
    CF_IO_MEDIA_NUM_TYPES = 0x6,
};

enum cf_io_access_types {
    CF_IO_ACCESS_NONE = 0xFFFFFFFF,
    CF_IO_ACCESS_STANDARD = 0x0,
    CF_IO_ACCESS_PACKFILE = 0x1,
    CF_IO_ACCESS_MEMORY = 0x2,
    CF_IO_ACCESS_UNKNOWN = 0x3,
    CF_IO_ACCESS_NUM_TYPES = 0x4,
};

enum cfmode_type {
    CF_MODE_NONE = 0x0,
    CF_MODE_READ = 0x1,
    CF_MODE_WRITE = 0x2,
};

enum cf_error_codes {
    CF_ERROR_NONE = 0x0,
    CF_ERROR_READ = 0x1,
    CF_ERROR_WRITE = 0x2,
    CF_ERROR_ABORT = 0x3,
    CF_ERROR_NUM_CODES = 0x4,
};

enum vlib_platform {
    PLATFORM_NONE = 0xffffffff,
    PLATFORM_PC = 0x0,
    PLATFORM_PS2 = 0x1,
    PLATFORM_PS3 = 0x2,
    PLATFORM_XBOX = 0x3,
    PLATFORM_XBOX2 = 0x4,
    PLATFORM_XBONE = 0x5,
    PLATFORM_PS4 = 0x6,
    PLATFORM_SWITCH = 0x7,
    NUM_VLIB_PLATFORMS = 0x8
};
struct cfile {
    char name[65];
    char full_pathname[257];
    cf_search_types m_searched_system;
    cf_io_access_types m_access_type;
    cfile_union ___u4;
    cf_io_media_types m_media_type;
    cfmode_type mode;
    cf_error_codes m_error_code;
    unsigned int pos;
    unsigned int size;
    unsigned int max_write_size;
    unsigned int m_flags;
};

struct v_packfile;
struct v_packfile_entry {
    char* name;
    unsigned int sector;
    unsigned int start;
    unsigned int hash;
    unsigned int size;
    unsigned int compressed_size;
    v_packfile* parent;
};

struct v_packfile_entry_serialized {
    et_ptr_offset<char, 0> name;
    unsigned int sector;
    unsigned int start;
    unsigned int hash;
    unsigned int size;
    unsigned int compressed_size;
    et_ptr_offset<v_packfile, 0> parent;
};

struct v_packfile {
    unsigned int descriptor;
    unsigned int version;
    char short_name[65];
    char pathname[256];
    unsigned int flags;
    unsigned int sector;
    unsigned int num_files;
    unsigned int file_size;
    unsigned int dir_size;
    unsigned int filename_size;
    unsigned int data_size;
    unsigned int compressed_data_size;
    v_packfile_entry* dir;
    v_packfile_entry_serialized* dir_serialized;
    char* filenames;
    char* data;
};

inline rfg::cfile* open_table_file(const char* file_name) {
    void* target = reinterpret_cast<void*>(utils::address::convert(OFFSET(0x005cd280, 0x005cd360)));
    rfg::cfile* result;

    asm volatile("call *%[func]"
                 : "=a"(result)
                 : [func] "r"(target), "S"(file_name)
                 : "memory", "cc");

    return result;
}
// REF_FUNC(open_table_file, cfile* __cdecl(const char* file_name), 0x005cd280);

REF_FUNC(cf_open,
         cfile* __cdecl(uint8_t* buffer, uint32_t buffer_size, const char* open_mode,
                        vlib_platform disk_platform),
         OFFSET(0x005b5bb0, 0x005c27f0));
REF_FUNC(cf_read,
         uint32_t __cdecl(void* dest_buffer, uint32_t num_bytes_to_read, cfile* file,
                          bool abortable),
         OFFSET(0x005c27e0, 0x005c28d0));
REF_FUNC(cf_close, bool __cdecl(cfile* file), OFFSET(0x005ca4b0, 0x005ca590));

// REF_VAR(g_packfiles, v_packfile*, 0x01ce1768);
// REF_VAR(g_packfile_count, int, 0x1CE767C);

} // namespace rfg
