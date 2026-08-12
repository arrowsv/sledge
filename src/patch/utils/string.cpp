#include "string.hpp"

#include <string>

namespace utils::string {
std::wstring widen_string(const std::string& string) {
    std::wstring wide_string;
    size_t size;
    wide_string.resize(string.length());
    mbstowcs_s(&size, &wide_string[0], wide_string.size() + 1, string.c_str(), string.size());
    return wide_string;
}

} // namespace utils::string
