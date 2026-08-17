#pragma once

#include <algorithm>
#include <string_view>

namespace utils {
inline std::string_view ltrim(std::string_view sv) {
    sv.remove_prefix(std::min(sv.find_first_not_of(" \t\n\r\f\v"), sv.size()));

    return sv;
}

// Удаление пробелов справа
inline std::string_view rtrim(std::string_view sv) {
    size_t end = sv.find_last_not_of(" \t\n\r\f\v");
    if (end != std::string_view::npos) {
        sv.remove_suffix(sv.size() - end - 1);
    } else {
        sv = "";
    }

    return sv;
}
} // namespace utils