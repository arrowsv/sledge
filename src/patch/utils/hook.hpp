#pragma once

#include "address.hpp"
#include <MinHook.h>
#include <stdexcept>

#include <safetyhook.hpp>

namespace utils::hook {
// #define HOOK_FUNC(offset, return_type, call_convention, name, ...)                             \
//     typedef return_type(call_convention *name##_t)(__VA_ARGS__);                               \
//     static name##_t name##_original_ptr = nullptr;                                             \
//     return_type call_convention name##_detour(__VA_ARGS__);                                    \
//     template<typename... Args>                                                                 \
//     inline return_type name##_original(Args... args)                                           \
//     {                                                                                          \
//         return name##_original_ptr(args...);                                                   \
//     }                                                                                          \
//     void name##_apply()                                                                        \
//     {                                                                                          \
//         if (MH_CreateHook((LPVOID)(utils::address::convert(offset)), (LPVOID) & name##_detour, \
//                           reinterpret_cast<LPVOID *>(&name##_original_ptr)) != MH_OK)          \
//         {                                                                                      \
//             throw std::runtime_error("Failed to create hook: " #name);                         \
//         }                                                                                      \
//         if (MH_EnableHook((LPVOID)(utils::address::convert(offset))) != MH_OK)                 \
//         {                                                                                      \
//             throw std::runtime_error("Failed to enable hook: " #name);                         \
//         }                                                                                      \
//     }                                                                                          \
//     return_type call_convention name##_detour(__VA_ARGS__)

#define HOOK_FUNC(offset, return_type, call_convention, name, ...)                                 \
    typedef return_type(call_convention* name##_t)(__VA_ARGS__);                                   \
    static SafetyHookInline name##_hook{};                                                         \
    return_type call_convention name##_detour(__VA_ARGS__);                                        \
    template <typename... Args> inline return_type name##_original(Args... args) {                 \
        return name##_hook.call<return_type>(args...);                                             \
    }                                                                                              \
    void name##_apply() {                                                                          \
        name##_hook =                                                                              \
            safetyhook::create_inline(reinterpret_cast<void*>(utils::address::convert(offset)),    \
                                      reinterpret_cast<void*>(&name##_detour));                    \
        if (!name##_hook) {                                                                        \
            throw std::runtime_error("Failed to create hook: " #name);                             \
        }                                                                                          \
    }                                                                                              \
    return_type call_convention name##_detour(__VA_ARGS__)
#define MID_HOOK_FUNC(offset, name)                                                                \
    static SafetyHookMid name##_mid_hook{};                                                        \
    void name##_mid_detour(SafetyHookContext& ctx);                                                \
    void name##_apply() {                                                                          \
        name##_mid_hook = safetyhook::create_mid(                                                  \
            reinterpret_cast<void*>(utils::address::convert(offset)), name##_mid_detour);          \
        if (!name##_mid_hook) {                                                                    \
            throw std::runtime_error("Failed to create mid hook: " #name);                         \
        }                                                                                          \
    }                                                                                              \
    void name##_mid_detour(SafetyHookContext& ctx)
} // namespace utils::hook
