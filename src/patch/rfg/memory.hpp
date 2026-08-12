#pragma once

namespace rfg {
struct mempool_base;
union mempool_base_vtable_union //$058DF3FFA7125B0957BD799298D7361D
{
    void*(__fastcall* mempool_base_destructor)(
        mempool_base* p_this,
        void* edx); // void(__fastcall * ~mempool_base)(mempool_base* p_this);
    void*(__fastcall* __vecDelDtor)(mempool_base* p_this, void* edx, unsigned int);
};

struct mempool_base_vtable {
    void(__fastcall* set_thread_ownership)(mempool_base* p_this, void* edx);
    unsigned char gap4[8];
    unsigned int(__fastcall* space_free)(mempool_base* p_this, void* edx);
    unsigned int(__fastcall* space_used)(mempool_base* p_this, void* edx);
    unsigned int(__fastcall* space_max)(mempool_base* p_this, void* edx);
    bool(__fastcall* can_alloc)(mempool_base* p_this, void* edx, unsigned int, unsigned int);
    void*(__fastcall* alloc)(mempool_base* p_this, void* edx, unsigned int, unsigned int);
    void*(__fastcall* realloc)(mempool_base* p_this, void* edx, void*, unsigned int);
    bool(__fastcall* contains_address)(mempool_base* p_this, void* edx, const void*);
    bool(__fastcall* clear)(mempool_base* p_this, void* edx);
    void*(__fastcall* get_base)(mempool_base* p_this, void* edx);
    unsigned int(__fastcall* mark)(mempool_base* p_this, void* edx);
    bool(__fastcall* restore_to_mark)(mempool_base* p_this, void* edx, unsigned int);
    bool(__fastcall* release_bytes)(mempool_base* p_this, void* edx, unsigned int);
    bool(__fastcall* pad_to_page)(mempool_base* p_this, void* edx, unsigned int);
    mempool_base_vtable_union vtable_union;
};

struct mempool_base {
    mempool_base_vtable* vfptr;
    volatile bool locked;
    volatile unsigned int lock_id;
    char name[32];
    char flags;
    volatile unsigned int thread_id;
    unsigned int peak_usage;

    void set_thread_ownership() { vfptr->set_thread_ownership(this, nullptr); }

    unsigned int space_free() { return vfptr->space_free(this, nullptr); }

    unsigned int space_used() { return vfptr->space_used(this, nullptr); }

    unsigned int space_max() { return vfptr->space_max(this, nullptr); }

    bool can_alloc(unsigned int size, unsigned int align) {
        return vfptr->can_alloc(this, nullptr, size, align);
    }

    void* alloc(unsigned int size, unsigned int align) {
        return vfptr->alloc(this, nullptr, size, align);
    }

    void* realloc(void* mem, unsigned int align) {
        return vfptr->realloc(this, nullptr, mem, align);
    }

    bool contains_address(const void* mem) { return vfptr->contains_address(this, nullptr, mem); }

    bool clear() { return vfptr->clear(this, nullptr); }

    void* get_base() { return vfptr->get_base(this, nullptr); }

    unsigned int mark() { return vfptr->mark(this, nullptr); }

    bool restore_to_mark(unsigned int pos) { return vfptr->restore_to_mark(this, nullptr, pos); }

    bool release_bytes(unsigned int numBytes) {
        return vfptr->release_bytes(this, nullptr, numBytes);
    }

    bool pad_to_page(unsigned int page_size) {
        return vfptr->pad_to_page(this, nullptr, page_size);
    }
};
} // namespace rfg
