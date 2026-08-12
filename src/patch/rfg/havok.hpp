#pragma once

namespace rfg {
struct hk_base_object_vtable;
struct hkp_world;
struct hkp_simulation_island;
struct hkp_entity;

struct hk_base_object {
    hk_base_object_vtable* vtable;
};

struct hk_referenced_object : hk_base_object {
    unsigned int m_memSizeAndRefCount;
};

struct hk_string_ptr {
    const char* m_stringAndFlag;
};

struct hkp_action : hk_referenced_object {
    hkp_world* m_world;
    hkp_simulation_island* m_island;
    unsigned int m_userData;
    hk_string_ptr m_name;
};

struct hkp_unary_action : hkp_action {
    hkp_entity* m_entity;
};
} // namespace rfg
